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

#ifndef QSL_INTEGRATION_H
#define QSL_INTEGRATION_H

#include <QSL/Object.h>

QSL_BEGIN_INTEGRATION_NAMESPACE

/**
 * @brief The QAGSIntegrator Uses the Gauss-Kronrod algorithm adaptively.
 */
class QSL_API QAGSIntegrator
    : public QSL::Object
{
public:

    QAGSIntegrator();

    virtual double function(double x) = 0;

    void integrate(double min, double max);

    void setErrorLimits(double epsAbs, double epsRel);

    double result() const;

    double error() const;

    quint32 intervals() const;
};

QSL_END_INTEGRATION_NAMESPACE

#endif // QSL_INTEGRATION_H
