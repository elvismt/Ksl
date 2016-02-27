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

#ifndef KSL_FIGURE_H
#define KSL_FIGURE_H

#include <Ksl/Object.h>
#include <QPainter>

KSL_BEGIN_NAMESPACE

// forward
class FigureScale;
class FigureItem;


class KSL_EXPORT Figure
    : public QObject
    , public Ksl::Object
{
    Q_OBJECT

public:

    Figure(const QString &name="Ksl", QObject *parent=0);

    virtual void add(FigureScale *scale);

    QList<FigureScale*>& scaleList();

    const QList<FigureScale*>& scaleList() const;

    QString name() const;

    FigureScale* scale(const QString &name) const;

    FigureItem* item(const QString &name) const;

    virtual void paint(const QRect &rect, QPainter *painter);


public slots:

    void setName(const QString &name);

    void setBackBrush(const QBrush &brush);

    virtual void save(const QString &filePath,
                      const QSize &size=QSize(500,400),
                      const char *format="png");

    virtual void onAppearenceChange(FigureItem *item);

    virtual void onDataChange(FigureItem *item);


signals:

    void changed(Figure *self);
    void errorOccured(Figure *self);


protected:

    Figure(Ksl::ObjectPrivate *priv,
           const QString &name, QObject *parent);
};

KSL_END_NAMESPACE

#endif // KSL_FIGURE_H
