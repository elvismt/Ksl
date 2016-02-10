#include <QApplication>
#include <QDebug>
#include <Ksl/chartview.h>
#include <Ksl/chartlinearscale.h>
#include <Ksl/simpleplot.h>
#include <cmath>

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    
    const quint32 nPts = 60;
    const double step = (M_PI-0.2)/nPts;
    const double xmin = -M_PI/2.0 + 0.1;
    QVector<double> x(nPts), y_sin(nPts),
        y_cos(nPts), y_tan(nPts);

    for (quint32 k=0; k<nPts; ++k) {
        x[k] = xmin + k*step;
        y_sin[k] = sin(x[k]);
        y_cos[k] = cos(x[k]);
        y_tan[k] = y_sin[k]/y_cos[k];
    }

    KslSimplePlot sin_plot(x, y_sin, "sin", Qt::red);
    KslSimplePlot cos_plot(x, y_cos, "cos", Qt::blue);
    KslSimplePlot tan_plot(x, y_tan, "tan", Qt::black);

    KslChartLinearScale scale;
    scale.add(sin_plot);
    scale.add(cos_plot);
    scale.add(tan_plot);

    KslChartView chart;
    chart.chart()->add(scale);
    chart.show();

    return app.exec();
}
