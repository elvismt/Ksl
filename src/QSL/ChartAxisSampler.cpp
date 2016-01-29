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


#include <QSL/ChartAxisSamplerPrivate.h>
#include <QList>

QSL_BEGIN_NAMESPACE

ChartAxisSampler::ChartAxisSampler()
    : QSL::Object(new ChartAxisSamplerPrivate(this))
{ }


ChartAxisSampler::SampleList& ChartAxisSampler::sampleList() {
    QSL_PUBLIC(ChartAxisSampler);
    return m->sampleList;
}


const ChartAxisSampler::SampleList& ChartAxisSampler::sampleList() const {
    QSL_PUBLIC(const ChartAxisSampler);
    return m->sampleList;
}


void ChartAxisSampler::add(const Sample &sample) {
    QSL_PUBLIC(ChartAxisSampler);
    m->mode = CustomSamples;
    m->sampleList.append(sample);
}


void ChartAxisSampler::setSamplesList(const SampleList &sampleList) {
    QSL_PUBLIC(ChartAxisSampler);
    m->mode = CustomSamples;
    m->sampleList.clear();
    m->sampleList.append(sampleList);
}


void ChartAxisSampler::setSamples(std::initializer_list<Sample> sampleList) {
    QSL_PUBLIC(ChartAxisSampler);
    m->mode = CustomSamples;
    m->sampleList.clear();
    for (auto &sample : sampleList) {
        m->sampleList.append(sample);
    }
}


void ChartAxisSampler::autoSampleDecimal(double min, double max, int hint) {
    QSL_PUBLIC(ChartAxisSampler);
    double coord;
    double firstTick;
    double vDiff, powDiff;
    double sampSpac;

    if (m->min == min && m->max == max && m->hint == hint) {
        return;
    }

    m->min = min;
    m->max = max;
    m->hint = hint;

    vDiff = max - min;
    powDiff = qRound(log10(vDiff));
    sampSpac = pow(10.0, powDiff-1.0);

    if ((vDiff/sampSpac) > (hint+5.0))
       sampSpac *= 2.0;
    if ((vDiff/sampSpac) < (hint-5.0))
       sampSpac /= 2.0;
    if ((vDiff/sampSpac) > (hint+5.0))
       sampSpac *= 2.0;
    if ((vDiff/sampSpac) < (hint-5.0))
       sampSpac /= 2.0;

    if (min < 0.0) {
        firstTick = -floor(fabs(min)/sampSpac) * sampSpac;
    } else {
        firstTick = floor(fabs(min)/sampSpac + 1.0) * sampSpac;
    }

    m->sampleList.clear();
    // sampSpac /= 4.0;
    coord = firstTick;
    while (coord <= max) {
        m->sampleList.append({QString::number(coord,'f',2), coord});
        coord += sampSpac;
    }
}


ChartAxisSampler::SamplingMode ChartAxisSampler::mode() const {
    QSL_PUBLIC(const ChartAxisSampler);
    return m->mode;
}

void ChartAxisSampler::setMode(SamplingMode mode) {
    QSL_PUBLIC(ChartAxisSampler);
    m->mode = mode;
}

QSL_END_NAMESPACE
