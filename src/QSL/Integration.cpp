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

#include <QSL/IntegrationPrivate.h>

QSL_BEGIN_INTEGRATION_NAMESPACE


static double qagsFunc(double x, void *params);


QAGSIntegrator::QAGSIntegrator()
    : QSL::Object(new QAGSIntegratorPrivate(this, 1.0e-5, 1.0e-5, 1000))
{
    QSL_PUBLIC(QAGSIntegrator);
    m->gslFunc.function = &qagsFunc;
    m->gslFunc.params = (void*) this;
}


QAGSIntegratorPrivate::~QAGSIntegratorPrivate() {
    gsl_integration_workspace_free(workspace);
}


void QAGSIntegrator::integrate(double min, double max) {
    QSL_PUBLIC(QAGSIntegrator);
    gsl_integration_qags(&m->gslFunc, min, max, m->epsAbs, m->epsRel,
                         m->maxIntervals, m->workspace, &m->result, &m->error);
}


double QAGSIntegrator::result() const {
    QSL_PUBLIC(const QAGSIntegrator);
    return m->result;
}


double QAGSIntegrator::error() const{
    QSL_PUBLIC(const QAGSIntegrator);
    return m->error;
}


quint32 QAGSIntegrator::intervals() const {
    QSL_PUBLIC(const QAGSIntegrator);
    return m->workspace->size;
}


void QAGSIntegrator::setErrorLimits(double epsAbs, double epsRel) {
    QSL_PUBLIC(QAGSIntegrator);
    m->epsAbs = epsAbs;
    m->epsRel = epsRel;
}


static double qagsFunc(double x, void *params) {
    QAGSIntegrator *integrator = (QAGSIntegrator*) params;
    return integrator->function(x);
}

QSL_END_INTEGRATION_NAMESPACE
