/*
 * Copyright (C) 2016  Elvis Teixeira
 *
 * This source code is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General
 * Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any
 * later version.
 *
 * This source code is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <Ksl/Csv_p.h>
#include <QFile>
#include <QDebug>
#include <QTextStream>

namespace Ksl {

Csv::Csv()
    : Ksl::Object(new CsvPrivate(this))
{ }

Csv::Csv(const QString &filePath,
         bool hasHeader, char delimiter)
    : Ksl::Object(new CsvPrivate(this))
{
    read(filePath, hasHeader, delimiter);
}


void Csv::read(const QString &filePath,
               bool hasHeader, char delimiter) {
    KSL_PUBLIC(Csv);

    m->filePath = filePath;
    QFile file(m->filePath);
    file.open(QIODevice::Text|QIODevice::ReadOnly);
    QTextStream str(&file);

    // read the headers of the columns
    // or create syntetic ones
    while (!str.atEnd()) {
        QString textLine = str.readLine();
        if (textLine.contains('#'))
            textLine.chop(textLine.size() - textLine.indexOf('#'));
        if (textLine.isEmpty())
            continue;

        QStringList line = textLine.split(delimiter, QString::SkipEmptyParts);
        if (hasHeader) {
            for (auto &label : line)
                m->dataBase[label.trimmed()] = QVector<QString>();
        }
        else {
            for (int k=1; k<line.size()+1; k++)
                m->dataBase[QString::number(k)] = QVector<QString>();
            bool seekOk = str.seek(0);
            if (!seekOk)
                qDebug() << "Error setting file pointer position";
        }
        break;
    }


    // read the data entries
    while (!str.atEnd()) {
        QString textLine = str.readLine();
        if (textLine.contains('#'))
            textLine.chop(textLine.size() - textLine.indexOf('#'));
        if (textLine.isEmpty())
            continue;

        QStringList line = textLine.split(delimiter, QString::SkipEmptyParts);
        auto lineIter = line.begin();
        for (auto &column : m->dataBase) {
            column.append(*lineIter++);
        }
    }
}


int Csv::rows() const {
    KSL_PUBLIC(const Csv);
    return (m->dataBase.begin())->size();
}

int Csv::cols() const {
    KSL_PUBLIC(const Csv);
    return m->dataBase.size();
}

Csv::StringData& Csv::data() {
    KSL_PUBLIC(Csv);
    return m->dataBase;
}


const Csv::StringData& Csv::data() const {
    KSL_PUBLIC(const Csv);
    return m->dataBase;
}


// buggy!
Array<1> Csv::column(const QString &columnLabel) const {
    KSL_PUBLIC(const Csv);
    if (!m->dataBase.contains(columnLabel))
        return Array<1>();

    QVector<QString> textColumn = m->dataBase[columnLabel];
    Array<1> ret(textColumn.size());
    bool ok = true;
    for (int k=0; k<textColumn.size(); ++k) {
        double value = textColumn[k].trimmed().toDouble(&ok);
        ret[k] = value;
        qDebug() << "text:" << textColumn[k];
        qDebug() << "double:" << value;
        if (!ok)
            qDebug() << "conversion to double failed!";
    }
    return std::move(ret);
}


Array<1,int> Csv::intColumn(const QString &columnLabel) const {
    KSL_PUBLIC(const Csv);
    if (!m->dataBase.contains(columnLabel))
        return Array<1,int>();

    QVector<QString> textColumn = m->dataBase[columnLabel];
    Array<1,int> ret(textColumn.size());
    bool ok = true;
    for (int k=0; k<textColumn.size(); ++k) {
        ret[k] = textColumn[k].trimmed().toInt(&ok);
    }
    return std::move(ret);
}


QVector<QString> Csv::stringColumn(const QString &columnLabel) const {
    KSL_PUBLIC(const Csv);
    if (!m->dataBase.contains(columnLabel))
        return QVector<QString>();

    QVector<QString> textColumn = m->dataBase[columnLabel];
    return std::move(textColumn);
}


Array<2> Csv::asMatrix() const {
    KSL_PUBLIC(const Csv);
    Array<2> mat(rows(), cols());
    int i=0;
    for (auto &column : m->dataBase) {
        for (int j=0; j<column.size(); ++j)
            mat[j][i] = column[j].trimmed().toDouble();
        ++i;
    }
    return std::move(mat);
}


Array<2> Csv::asMatrixTransposed() const {
    KSL_PUBLIC(const Csv);
    Array<2> mat(cols(), rows());
    int i=0;
    for (auto &column : m->dataBase) {
        for (int j=0; j<column.size(); ++j)
            mat[i][j] = column[j].trimmed().toDouble();
        ++i;
    }
    return std::move(mat);
}

} // namespace Ksl
