/*
 * Copyright (C) 2016  Elvis M.Teixeira
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


#ifndef QSL_CHARTAXISSAMPLER_H
#define QSL_CHARTAXISSAMPLER_H

#include <QSL/Object.h>
#include <QString>
#include <QList>

QSL_BEGIN_NAMESPACE

class QSL_API ChartAxisSampler
    : public QSL::Object
{
public:

    enum SamplingMode {
        AutoDecimal,
        CustomSamples
    };


    enum SampleType {
        MajorSample,
        MinorSample,
        DummySample
    };


    struct Sample {

        Sample(const QString &ilabel, qreal icoord,
               SampleType itype=MajorSample)
            : label(ilabel)
            , coord(icoord)
            , type(itype)
        { }

        QString label;
        qreal coord;
        SampleType type;
    };


    typedef QList<Sample> SampleList;


    ChartAxisSampler();


    SampleList& sampleList();
    const SampleList& sampleList() const;


    void add(const Sample &sample);
    void setSamplesList(const SampleList &sampleList);
    void setSamples(std::initializer_list<Sample> sampleList);
};

QSL_END_NAMESPACE

#endif // QSL_CHARTAXISSAMPLER_H
