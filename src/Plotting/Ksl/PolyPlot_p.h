
#ifndef KSL_POLYPLOT_P_H
#define KSL_POLYPLOT_P_H

#include <Ksl/PolyPlot.h>
#include <Ksl/FigureItem_p.h>

namespace Ksl {

class PolyPlotPrivate
    : public FigureItemPrivate
{
public:

    PolyPlotPrivate(PolyPlot *publ)
        : FigureItemPrivate(publ)
        , antialias(true)
        , pointCount(50)
    { }


    bool antialias;
    uint32_t pointCount;

    QPen pen;

    Array<1> a;
    Array<1> x, y;

    double xMin, xMax;
    double yMin, yMax;
};

} // namespace Ksl

#endif // KSL_POLYPLOT_P_H
