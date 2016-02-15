#include <QApplication>
#include <QDebug>
#include <Ksl/chartview.h>
#include <Ksl/chartlinscale.h>
#include <Ksl/simpleplot.h>
#include <cmath>

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    
    auto x = linspace(0.0, 2.0*M_PI, 0.05);
    auto y_sin = apply(sin, x);
    auto y_cos = apply(cos, x);

    KslSimplePlot sin_plot(x, y_sin, "sin", Qt::red);
    KslSimplePlot cos_plot(x, y_cos, "cos", Qt::blue);

    KslChartLinscale scale;
    scale.add(sin_plot);
    scale.add(cos_plot);

    KslChartView chart;
    chart.chart()->add(scale);
    chart.show();

    return app.exec();
}
