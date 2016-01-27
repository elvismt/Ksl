#include <QSL/FigureItemPrivate.h>
#include <QSL/FigureScale.h>
#include <QSL/Figure.h>

QSL_BEGIN_NAMESPACE

QString FigureItem::name() const {
    QSL_PUBLIC(const FigureItem);
    return m->name;
}


bool FigureItem::visible() const {
    QSL_PUBLIC(const FigureItem);
    return m->visible;
}


FigureScale* FigureItem::scale() const {
    QSL_PUBLIC(const FigureItem);
    return m->scale;
}


Figure* FigureItem::figure() const {
    QSL_PUBLIC(const FigureItem);
    return m->figure;
}


void FigureItem::setScale(FigureScale *scale) {
    QSL_PUBLIC(FigureItem);

    Figure *oldFigure = m->figure;
    Figure *newFigure = scale != nullptr ? scale->figure() : nullptr;

    m->scale = scale;
    m->figure = newFigure;

    if (oldFigure != nullptr) {
        disconnect(this, SIGNAL(appearenceChange(FigureItem*)),
                   oldFigure, SLOT(handleAppearenceChange(FigureItem*)));
        disconnect(this, SIGNAL(dataChange(FigureItem*)),
                   oldFigure, SLOT(handleDataChange(FigureItem*)));
    }

    if (newFigure != nullptr) {
        connect(this, SIGNAL(appearenceChange(FigureItem*)),
                newFigure, SLOT(handleAppearenceChange(FigureItem*)));
        connect(this, SIGNAL(dataChange(FigureItem*)),
                newFigure, SLOT(handleDataChange(FigureItem*)));
    }
}

QSL_END_NAMESPACE
