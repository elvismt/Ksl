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

#ifndef KSL_CHARTAXISSAMPLER_H
#define KSL_CHARTAXISSAMPLER_H

#include <Ksl/Object.h>
#include <QList>

KSL_BEGIN_NAMESPACE

class KSL_EXPORT ChartAxisSampler
    : public Ksl::Object
{
public:

    enum Mode {
        CustomSamples,
        AutoDecimal
    };


    struct Sample {
        Sample(const QString &ilabel, double icoord)
            : label(ilabel)
            , coord(icoord)
        { }

        Sample(const char *ilabel, double icoord)
            : label(QString::fromUtf8(ilabel))
            , coord(icoord)
        { }

        QString label;
        double coord;
    };


    ChartAxisSampler();

    QList<Sample>& sampleList();
    const QList<Sample>& sampleList() const;

    void setMode(Mode mode);

    void setSamples(const QList<Sample> &samples);

#if !defined(_MSC_VER) || _MSC_VER > 1700
    void setSamples(std::initializer_list<Sample> initList);
#endif
};

KSL_END_NAMESPACE

#endif // KSL_CHARTAXISSAMPLER_H
