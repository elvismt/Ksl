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
#include <QVector>

namespace Ksl {

class KSL_EXPORT Csv
    : public Ksl::Object
{
public:

    Csv();

    Csv(const QString &filePath,
        bool hasHeader=true, char delimiter=' ');


    virtual bool readAll(const QString &filePath,
                         bool hasHeader=true, char delimiter=' ');

    int rows() const;

    int cols() const;

    bool empty() const;

    const QVector<QString> column(const QString &key) const;

    const QVector<QString> column(int index) const;

    Array<1> array(const QString &key) const;

    Array<1> array(int index) const;

    Array<2> matrix() const;

    Array<2> submatrix(int i, int j, int rows, int cols) const;
};

} // namespace Ksl

#endif // KSL_CSV_H
