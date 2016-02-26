#ifndef KSL_CANVAS_P_H
#define KSL_CANVAS_P_H

#include <Ksl/Canvas.h>
#include <QtWidgets>

KSL_BEGIN_NAMESPACE

class CanvasPrivate;


class CanvasDrawingArea
    : public QWidget
{
public:

    CanvasDrawingArea(int width, int height,
                      Canvas *canvas, CanvasPrivate *canvPriv);

    QSize sizeHint() const;

    void paintEvent(QPaintEvent *event);

    void mousePressEvent(QMouseEvent *event);

    Canvas *canvas;
    CanvasPrivate *canvPriv;
    QSize defaultSize;
    QPainter *painter;
};


class CanvasPrivate
    : public Ksl::ObjectPrivate
{
public:

    CanvasPrivate(Canvas *publ, int width, int height)
        : Ksl::ObjectPrivate(publ)
        , drawingArea(new CanvasDrawingArea(width, height, publ, this))
    { }

    CanvasDrawingArea *drawingArea;
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
};

KSL_END_NAMESPACE

#endif // KSL_CANVAS_P_H
