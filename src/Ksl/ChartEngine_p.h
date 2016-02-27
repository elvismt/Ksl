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

#ifndef KSL_CHARTENGINE_P_H
#define KSL_CHARTENGINE_P_H

#include <Ksl/ChartEngine.h>
#include <QBrush>

KSL_BEGIN_NAMESPACE

class ChartEnginePrivate
    : public Ksl::ObjectPrivate
{
public:

    ChartEnginePrivate(ChartEngine *publ, const QString &iname)
        : Ksl::ObjectPrivate(publ)
#if defined(Q_OS_WIN32)
        , font("Times New Roman", 11)
#elif defined(Q_OS_LINUX)
        // let system decide
        //, font("FreeMono", 10)
#endif
        , name(iname)
        , showName(true)
        , nameColor(Qt::black)
        , backBrush(Qt::white)
        , colorTheme(ChartEngine::LightTheme)
        , paintBack(true)
        , onError(false)
    { }

    QFont font;
    QString name;
    bool showName;
    QColor nameColor;
    QBrush backBrush;
    ChartEngine::ColorTheme colorTheme;
    bool paintBack;
    bool onError;
    QList<ChartScale*> scaleList;
};

KSL_END_NAMESPACE

#endif // KSL_CHARTENGINE_P_H
