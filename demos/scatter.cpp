#include <QApplication>
#include <QDebug>
#include <Ksl/chartview.h>
#include <Ksl/chartlinscale.h>
#include <Ksl/simpleplot.h>
#include <cmath>

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    // five thousand points
    auto x = linspace(0.0, 5000.0);
    auto y = randspace(5000.0, 10.0);

    KslSimplePlot scatter(x, y, "scatter", Qt::black, Qt::green,
                          KslSimplePlot::Circles);

    KslChartLinscale scale;
    scale.add(scatter);

    KslChartView chart;
    chart.chart()->add(scale);
    chart.show();

    return app.exec();
}
