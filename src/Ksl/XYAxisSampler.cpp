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

#include <Ksl/XYAxisSampler_p.h>

namespace Ksl {

XYAxisSampler::XYAxisSampler()
    : Ksl::Object(new XYAxisSamplerPrivate(this))
{ }


QList<XYAxisSampler::Sample>& XYAxisSampler::sampleList() {
    KSL_PUBLIC(XYAxisSampler);
    return m->sampleList;
}


const QList<XYAxisSampler::Sample>& XYAxisSampler::sampleList() const {
    KSL_PUBLIC(const XYAxisSampler);
    return m->sampleList;
}


bool XYAxisSampler::minorSamples() const {
    KSL_PUBLIC(const XYAxisSampler);
    return m->minorSamples;
}


void XYAxisSampler::addMinorSamples(bool on) {
    KSL_PUBLIC(XYAxisSampler);
    m->minorSamples = on;
}


XYAxisSampler::Mode XYAxisSampler::mode() const {
    KSL_PUBLIC(const XYAxisSampler);
    return m->mode;
}

void XYAxisSampler::setMode(Mode mode) {
    KSL_PUBLIC(XYAxisSampler);
    m->mode = mode;
}


void XYAxisSampler::setSampleList(const QList<Sample> &samples) {
    KSL_PUBLIC(XYAxisSampler);
    m->mode = CustomSamples;
    m->sampleList.clear();
    m->sampleList = samples;
}


#ifdef Q_COMPILER_INITIALIZER_LISTS
void XYAxisSampler::setSamples(std::initializer_list<Sample> initList) {
    KSL_PUBLIC(XYAxisSampler);
    m->mode = CustomSamples;
    m->sampleList.clear();
    for (auto &sample : initList)
        m->sampleList.append(sample);
}
#endif


void XYAxisSampler::addSample(const QString &label, double coord, bool isMajor) {
    KSL_PUBLIC(XYAxisSampler);
    m->mode = CustomSamples;
    m->sampleList.append(Sample(label, coord, isMajor));
}


void XYAxisSampler::autoSampleDecimal(double min, double max, double hint) {
    KSL_PUBLIC(XYAxisSampler);
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
    if (m->minorSamples)
        sampSpac /= 4.0;
    double coord = firstTick;
    int k = 0;
    while (coord <= max) {
        if (m->minorSamples) {
            if (k%4 == 0) {
                // Sometimes the zero coord falls not exactly on zero
                // and you get something like -124345e-301. Weird ya?
                if (fabs(coord) / valDiff < 1.0e-10 && valDiff > 1.0e-10)
                    coord = 0.0;
                m->sampleList.append(
                    Sample(QString("%1").arg(coord, 0, 'f', 1), coord));
            }
            else
                m->sampleList.append(Sample(QString(), coord, false));
        }
        else { // No minor samples
            if (fabs(coord) / valDiff < 1.0e-10 && valDiff > 1.0e-10)
                coord = 0.0;
            m->sampleList.append(
                Sample(QString("%1").arg(coord, 0, 'f', 1), coord));
        }
        coord += sampSpac;
        k += 1;
    }
}

} // namespace Ksl
