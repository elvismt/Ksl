#ifndef KSL_CANVAS_H
#define KSL_CANVAS_H

#include <Ksl/Object.h>
#include <QMainWindow>

KSL_BEGIN_NAMESPACE

class KSL_EXPORT Canvas
    : public QMainWindow
    , public Ksl::Object
{
public:

    Canvas(const QString &title="Ksl", int width=500,
           int height=500, QWidget *parent=0);

    virtual ~Canvas();

    virtual void paint(QPainter *painter, const QRect &rect);

    virtual void leftClick(const QPoint &pos);

    virtual void rightClick(const QPoint &pos);
};

KSL_END_NAMESPACE

#endif // KSL_CANVAS_H
