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

#ifndef QSL_INTEGRATIONPRIVATE_H
#define QSL_INTEGRATIONPRIVATE_H

#include <QSL/Integration.h>
#include <gsl/gsl_integration.h>

QSL_BEGIN_INTEGRATION_NAMESPACE

class QAGSIntegratorPrivate
    : public QSL::ObjectPrivate
{
public:

    QAGSIntegratorPrivate(QAGSIntegrator *publ, double iepsAbs,
                          double iepsRel, quint32 imaxIntervals)
        : QSL::ObjectPrivate(publ)
        , workspace(gsl_integration_workspace_alloc(1000))
        , maxIntervals(imaxIntervals)
        , epsRel(iepsRel)
        , epsAbs(iepsAbs)
    { }

    ~QAGSIntegratorPrivate();


    gsl_integration_workspace *workspace;
    gsl_function gslFunc;
    quint32 maxIntervals;
    double epsRel;
    double epsAbs;
    double error;
    double result;
};

QSL_END_INTEGRATION_NAMESPACE

#endif // QSL_INTEGRATIONPRIVATE_H
