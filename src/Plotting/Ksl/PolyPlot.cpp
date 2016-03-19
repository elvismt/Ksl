
#include <Ksl/PolyPlot_p.h>
#include <Ksl/FigureScale.h>

namespace Ksl {

PolyPlot::PolyPlot(const Array<1> &a, const QColor &color,
                   double xmin, double xmax,
                   const QString &name, QObject *parent)
    : FigureItem(new PolyPlotPrivate(this), name, parent)
{
    KSL_PUBLIC(PolyPlot);

    m->a = copy(a);
    m->pen.setColor(color);
    m->pen.setWidth(2);

    // create arrays
    m->x = linspace(xmin, xmax, (xmax-xmin)/m->pointCount);
    m->y = samesize(m->x);

    // calculate functional values
    for (uint32_t k=0; k<m->pointCount; ++k) {
        m->y[k] = poly(m->a, m->x[k]);
    }

    // set data ranges
    m->xMin = xmin;
    m->xMax = xmax;
    m->yMin = m->y[0];
    m->yMax = m->y[0];
    for (uint32_t k=1; k<m->pointCount; ++k) {
        if (m->y[k] < m->yMin) m->yMin = m->y[k];
        if (m->y[k] > m->yMax) m->yMax = m->y[k];
    }
}


QRectF PolyPlot::dataRect() const {
    KSL_PUBLIC(const PolyPlot);
    return QRectF(m->xMin, m->yMin,
                  m->xMax - m->xMin,
                  m->yMax - m->yMin);
}


void PolyPlot::paint(QPainter *painter) {
    KSL_PUBLIC(PolyPlot);
    painter->setRenderHint(QPainter::Antialiasing, m->antialias);
    painter->setPen(m->pen);

    QPoint p1 = m->scale->map(QPointF(m->x[0], m->y[0]));
    for (uint32_t k=1; k<m->pointCount; ++k) {
        QPoint p2 = m->scale->map(QPointF(m->x[k], m->y[k]));
        painter->drawLine(p1, p2);
        p1 = p2;
    }
}

} // namespace Ksl
