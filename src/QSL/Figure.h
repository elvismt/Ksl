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

#ifndef QSL_FIGURE_H
#define QSL_FIGURE_H

#include <QSL/Object.h>
#include <QPainter>
#include <QObject>

QSL_BEGIN_NAMESPACE

class FigureScale;
class FigureItem;

class QSL_API Figure
    : public QObject
    , public QSL::Object
{
    Q_OBJECT

public:

    typedef QList<FigureScale*> ScaleList;


    Figure(const QString &name="QSL", QObject *parent = 0);


    QString name() const;
    QPen titlePen() const;
    bool showTitle() const;

    ScaleList& scaleList();
    const ScaleList& scaleList() const;

    FigureScale* scale(const QString &name) const;
    FigureItem* item(const QString &name) const;

    void add(FigureScale *scale);
    inline void add(FigureScale &scale) { add(&scale); }

    virtual void paint(const QRect &targetRect, QPainter *painter);

    virtual void save(const QString &fileName,
                      const QSize &size=QSize(500,350),
                      const char *fileFormat="png");


public Q_SLOTS:

    void setTitlePen(const QPen &pen);
    void setShowTitle(bool showTitle);

    virtual void handleAppearenceChange(FigureItem *item);
    virtual void handleDataChange(FigureItem *item);


Q_SIGNALS:

    void change(Figure *self);
    void error(Figure *figure);


protected:

    Figure(ObjectPrivate *priv, QObject *parent)
        : QObject(parent)
        , QSL::Object(priv)
    { }
};

QSL_END_NAMESPACE

#endif // QSL_FIGURE_H
