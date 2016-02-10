#include <QApplication>
#include <QDebug>
#include <Ksl/chartview.h>
#include <Ksl/chartlinearscale.h>
#include <Ksl/simpleplot.h>
#include <cmath>

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    // two thousand points
    const quint32 nPts = 2000;
    QVector<double> x(nPts), y(nPts);

    for (quint32 k=0; k<nPts; ++k) {
        x[k] = 10.0 * double(rand())/RAND_MAX;
        y[k] = 10.0 * double(rand())/RAND_MAX;
    }

    KslSimplePlot scatter(x, y, "scatter", Qt::black, Qt::green,
                          KslSimplePlot::Circles);

    KslChartLinearScale scale;
    scale.add(scatter);

    KslChartView chart;
    chart.chart()->add(scale);
    chart.show();

    return app.exec();
}
