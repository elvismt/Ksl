#include <QApplication>
#include <Ksl/ChartView.h>
#include <Ksl/ChartLinscale.h>
#include <Ksl/SeriesPlot.h>
#include <cmath>
using namespace Ksl;

double wave(double x) {
    return sin(2*x) + 0.2*cos(10*x);
}

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    auto x = linspace(0.0, 6.29, 0.1);
    auto ysin = applyed(sin, x);
    auto ycos = applyed(cos, x);
    auto ywave = applyed(wave, x);

    SeriesPlot splot(x, ysin, SeriesPlot::Line, Qt::blue);
    SeriesPlot cplot(x, ycos, SeriesPlot::Line, Qt::red);
    SeriesPlot wplot(x, ywave, SeriesPlot::Line, Qt::green);

    ChartLinscale scale;
    scale.add(splot);
    scale.add(cplot);
    scale.add(wplot);

    ChartView view;
    view.chart()->add(scale);
    view.show();

    return app.exec();
}
