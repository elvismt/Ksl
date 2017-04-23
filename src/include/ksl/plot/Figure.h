/*
 * Copyright (C) 2017  Elvis Teixeira
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

#pragma once
#include <ksl/Object.h>
#include <QObject>
#include <QRect>

// Qt forward declarations
QT_BEGIN_NAMESPACE
class QPainter;
class QMouseEvent;
QT_END_NAMESPACE

namespace ksl {
namespace plot {

// forward declarations
class FigureScale;
class FigureItem;
class FigureView;

class Figure:
    public QObject,
    public ksl::Object
{
    Q_OBJECT

public:

    FigureView* view() const;

    Figure(const QString &title="Ksl", QObject *parent=nullptr);

    virtual void addScale(FigureScale *scale);

    QList<FigureScale*>& scaleList();

    const QList<FigureScale*>& scaleList() const;

    FigureScale* scale(const QString &title) const;

    FigureItem* item(const QString &title) const;

    virtual void paint(const QRect &rect, QPainter *painter);

    void save(const QString fileName, int width=500,
              int height=350, const char *format="png");


public slots:

    void notifyError();

    void notifyChange();

    virtual void onDataChange(FigureItem *item);

    virtual void onAppearenceChange(FigureItem *item);


signals:

    void errorOccured();

    void changeOccured();


protected:

    friend class FigureView;

    Figure(ksl::ObjectPrivate *priv, QObject *parent=nullptr);

    virtual void setView(FigureView *view);

    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void mouseDoubleClickEvent(QMouseEvent *event);
};
}}
