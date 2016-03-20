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

#ifndef KSL_CSV_H
#define KSL_CSV_H

#include <Ksl/Object.h>
#include <Ksl/Array.h>
#include <QStringList>
#include <QHash>
#include <QVector>

namespace Ksl {

class KSL_EXPORT Csv
    : public Ksl::Object
{
public:

    typedef QStringList Row;
    typedef QHash< QString, QVector<QString> > StringData;


    Csv();

    Csv(const QString &filePath,
        bool hasHeader=true, char delimiter=' ');


    virtual void read(const QString &filePath,
                      bool hasHeader=true, char delimiter=' ');

    int rows() const;

    int cols() const;


    StringData& data();

    const StringData& data() const;


    Array<1> column(const QString &columnLabel) const;

    Array<1,int> intColumn(const QString &columnLabel) const;

    QVector<QString> stringColumn(const QString &columnLabel) const;

    Array<2> asMatrix() const;

    Array<2> asMatrixTransposed() const;

};

} // namespace Ksl

#endif // KSL_CSV_H
