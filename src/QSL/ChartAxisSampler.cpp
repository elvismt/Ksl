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
    m->sampleList.append(sample);
}


void ChartAxisSampler::setSamples(const SampleList &sampleList) {
    QSL_PUBLIC(ChartAxisSampler);
    m->sampleList.clear();
    m->sampleList.append(sampleList);
}


void ChartAxisSampler::setSamples(std::initializer_list<Sample> sampleList) {
    QSL_PUBLIC(ChartAxisSampler);
    m->sampleList.clear();
    for (auto &sample : sampleList) {
        m->sampleList.append(sample);
    }
}

QSL_END_NAMESPACE
