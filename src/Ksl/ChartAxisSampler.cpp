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

#include <Ksl/ChartAxisSampler_p.h>

KSL_BEGIN_NAMESPACE

ChartAxisSampler::ChartAxisSampler()
    : Ksl::Object(new ChartAxisSamplerPrivate(this))
{ }


QList<ChartAxisSampler::Sample>& ChartAxisSampler::sampleList() {
    KSL_PUBLIC(ChartAxisSampler);
    return m->sampleList;
}


const QList<ChartAxisSampler::Sample>& ChartAxisSampler::sampleList() const {
    KSL_PUBLIC(const ChartAxisSampler);
    return m->sampleList;
}


ChartAxisSampler::Mode ChartAxisSampler::mode() const {
    KSL_PUBLIC(const ChartAxisSampler);
    return m->mode;
}

void ChartAxisSampler::setMode(Mode mode) {
    KSL_PUBLIC(ChartAxisSampler);
    m->mode = mode;
}


void ChartAxisSampler::setSamples(const QList<Sample> &samples) {
    KSL_PUBLIC(ChartAxisSampler);
    m->mode = CustomSamples;
    m->sampleList.clear();
    m->sampleList = samples;
}


#if !defined(_MSC_VER) || _MSC_VER > 1700
void ChartAxisSampler::setSamples(std::initializer_list<Sample> initList) {
    KSL_PUBLIC(ChartAxisSampler);
    m->mode = CustomSamples;
    m->sampleList.clear();
    for (auto &sample : initList)
        m->sampleList.append(sample);
}
#endif


void ChartAxisSampler::addSample(const QString &label, double coord, bool isMajor) {
    KSL_PUBLIC(ChartAxisSampler);
    m->mode = CustomSamples;
    m->sampleList.append(Sample(label, coord, isMajor));
}


void ChartAxisSampler::autoSampleDecimal(double min, double max, double hint) {
    KSL_PUBLIC(ChartAxisSampler);
    double firstTick;
    double valDiff, powDiff;
    double sampSpac;

    if (m->min == min && m->max == max && m->hint == hint) {
        return;
    }
    m->min = min;
    m->max = max;
    m->hint = hint;

    valDiff = max - min;
    powDiff = qRound(log10(valDiff));
    sampSpac = pow(10.0, powDiff-1.0);

    if ((valDiff/sampSpac) > (hint+5.0))
        sampSpac *= 2.0;
    if ((valDiff/sampSpac) < (hint-5.0))
        sampSpac /= 2.0;
    if ((valDiff/sampSpac) > (hint+5.0))
        sampSpac *= 2.0;
    if ((valDiff/sampSpac) < (hint-5.0))
        sampSpac /= 2.0;

    if (min < 0.0) {
       firstTick = -floor(fabs(min)/sampSpac) * sampSpac;
    } else {
       firstTick = floor(fabs(min)/sampSpac + 1.0) * sampSpac;
    }

    m->sampleList.clear();
    sampSpac /= 4.0;
    double coord = firstTick;
    int k = 0;
    while (coord <= max) {
        if (k%4 == 0) {
            // Sometimes the zero coord falls not exactly on zero
            // and you get something like -124345e-301. Weird ya?
            if (fabs(coord) / valDiff < 1.0e-10 && valDiff > 1.0e-10)
                coord = 0.0;
            m->sampleList.append(Sample(QString::number(coord,'g'), coord));
        }
        else
            m->sampleList.append(Sample(QString(), coord, false));
        coord += sampSpac;
        k += 1;
    }
}

KSL_END_NAMESPACE
