#include <QApplication>
#include <Ksl/ChartView.h>
#include <Ksl/ChartLinscale.h>
#include <Ksl/SeriesPlot.h>
#include <Ksl/Math.h>
using namespace Ksl;

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    auto x = linspace(0.0, 6.29, 0.1);
    SeriesPlot splot(x, apply(Math::sin, x), SeriesPlot::Line, Qt::blue);
    SeriesPlot cplot(x, apply(Math::cos, x), SeriesPlot::Line, Qt::red);

    ChartLinscale scale;
    scale.add(splot);
    scale.add(cplot);

    ChartView view;
    view.chart()->add(scale);
    view.show();

    return app.exec();
}
