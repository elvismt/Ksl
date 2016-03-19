#ifndef KSL_POLYPLOT_H
#define KSL_POLYPLOT_H

#include <Ksl/FigureItem.h>
#include <Ksl/Functions.h>

namespace Ksl {

class KSL_EXPORT PolyPlot
    : public FigureItem
{
    Q_OBJECT

public:

    PolyPlot(const Array<1> &a, const QColor &color=Qt::red,
             double xmin=-3.0, double xmax=3.0,
             const QString &name="poly", QObject *parent=0);


    virtual QRectF dataRect() const;


protected:

    virtual void paint(QPainter *painter);
};

} // namespace Ksl

#endif // KSL_POLYPLOT_H
