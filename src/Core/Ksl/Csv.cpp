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
    readAll(filePath, hasHeader, delimiter);
}


bool Csv::readAll(const QString &filePath,
               bool hasHeader, char delimiter) {
    KSL_PUBLIC(Csv);

    m->filePath = filePath;
    QFile file(m->filePath);
    if (!file.open(QIODevice::Text|QIODevice::ReadOnly)) {
        qDebug() << "Csv::readAll: File not found!";
        return false;
    }
    QTextStream str(&file);

    while (!str.atEnd()) {
        QString line = str.readLine();
        if (int k = line.indexOf('#') > -1)
            line.chop(line.size() - k);
        if (line.isEmpty())
            continue;

        QStringList attrs = line.split(
            delimiter, QString::SkipEmptyParts);
        if (hasHeader) {
            for (auto &label : attrs) {
                m->keys.append(label.trimmed());
                m->columns.append(QVector<QString>());
            }
        }
        else {
            for (int k=1; k<attrs.size()+1; k++) {
                m->keys.append(QString::number(k));
                m->columns.append(QVector<QString>());
            }
            if (!str.seek(0))
                qDebug() << "SEEK error!";
        }
        break;
    }

    while (!str.atEnd()) {
        QString line = str.readLine();
        if (int k = line.indexOf('#') > -1)
            line.chop(line.size() - k);
        if (line.isEmpty())
            continue;

        QStringList attrs = line.split(
            delimiter, QString::SkipEmptyParts);
        auto iter = attrs.begin();
        for (auto &column : m->columns) {
            column.append(*iter++);
        }
    }
    m->empty = false;
    return true;
}


bool Csv::empty() const {
    KSL_PUBLIC(const Csv);
    return m->empty;
}


int Csv::rows() const {
    KSL_PUBLIC(const Csv);
    return m->columns[0].size();
}


int Csv::cols() const {
    KSL_PUBLIC(const Csv);
    return m->keys.size();
}


const QVector<QString> Csv::column(const QString &key) const {
    KSL_PUBLIC(const Csv);
    if (!m->keys.contains(key))
        return QVector<QString>();
    return m->columns.at(m->keys.indexOf(key));
}


const QVector<QString> Csv::column(int index) const {
    KSL_PUBLIC(const Csv);
    return m->columns[index];
}


Array<1> Csv::array(const QString &key) const {
    auto column = this->column(key);
    if (column.isEmpty())
        return Array<1>();

    Array<1> ret(column.size());
    for (int k=0; k<column.size(); ++k)
        ret[k] = column[k].trimmed().toDouble();

    return std::move(ret);
}


Array<1> Csv::array(int index) const {
    KSL_PUBLIC(const Csv);
    return array(m->keys[index]);
}


Array<2> Csv::matrix() const {
    KSL_PUBLIC(const Csv);
    Array<2> mat(rows(), cols());
    int i=0;
    for (auto &column : m->columns) {
        for (int j=0; j<column.size(); ++j)
            mat[j][i] = column[j].trimmed().toDouble();
        ++i;
    }
    return std::move(mat);
}

Array<2> Csv::submatrix(int i, int j, int rows, int cols) const {
    KSL_PUBLIC(const Csv);
    Array<2> mat(rows, cols);

    auto coliter = m->columns.begin();
    for (int k=0; k<j; ++k)
        ++coliter;

    for (int k=0; k<cols; ++k) {
        for (int l=i; l<rows; ++l) {
            mat[l-i][k] = (*coliter)[l].trimmed().toDouble();
        }
        ++coliter;
    }
    return std::move(mat);
}

} // namespace Ksl
