#ifndef QSL_FIGUREITEM_H
#define QSL_FIGUREITEM_H

#include <QSL/Object.h>
#include <QObject>
#include <QPainter>

QSL_BEGIN_NAMESPACE

// forward declaration
class Figure;
class FigureScale;

class QSL_API FigureItem
    : public QObject
    , public QSL::Object
{
    Q_OBJECT

public:


    QString name() const;
    bool visible() const;

    FigureScale* scale() const;
    Figure* figure() const;


    virtual QRect figureRect() const = 0;
    virtual QRectF dataRect() const = 0;


Q_SIGNALS:

    void dataChange(FigureItem *self);
    void appearenceChange(FigureItem *self);

protected:

    friend class FigureScale;

    virtual void paint(QPainter *painter) = 0;

    virtual void setScale(FigureScale *scale);


    FigureItem(ObjectPrivate *priv, QObject *parent = 0)
        : QObject(parent)
        , QSL::Object(priv)
    { }
};

QSL_END_NAMESPACE

#endif // QSL_FIGUREITEM_H
