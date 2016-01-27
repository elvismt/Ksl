#ifndef QSL_FIGUREITEMPRIVATE_H
#define QSL_FIGUREITEMPRIVATE_H

#include <QSL/FigureItem.h>

QSL_BEGIN_NAMESPACE

class FigureItemPrivate
    : public ObjectPrivate
{
public:

    FigureItemPrivate(FigureItem *publ, const QString &name)
        : ObjectPrivate(publ)
        , name("Figure Item")
        , visible(true)
        , scale(nullptr)
        , figure(nullptr)
    { }


    QString name;
    bool visible;
    FigureScale *scale;
    Figure *figure;
};

QSL_END_NAMESPACE

#endif // QSL_FIGUREITEMPRIVATE_H
