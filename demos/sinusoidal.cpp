#include <QApplication>
#include <Ksl/ChartView.h>
#include <Ksl/ChartLinscale.h>
#include <Ksl/SeriesPlot.h>
using namespace Ksl;

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    auto x = linspace(-M_PI, M_PI, 0.05);
    ChartLinscale scales[3];
    ChartView views[3];

    // Add sme functions
    scales[0].add(new SeriesPlot(x, sin(x), "Sin(X)", Qt::red));
    views[0].setWindowTitle("SIN");

    scales[1].add(new SeriesPlot(x, cos(x), "Cos(X)", Qt::green));
    views[1].setWindowTitle("COS");

    scales[2].add(new SeriesPlot(x, tan(x), "Tan(X)", Qt::blue));
    views[2].setWindowTitle("TAN");

    for (int k=0; k<3; ++k) {
        // We will use custom axis labels, in terms of pi
        auto sampler = scales[k].axis(X_Axis)->sampler();
        sampler->addSample("-π", -M_PI);
        sampler->addSample("-π/2", -M_PI/2);
        sampler->addSample("π/2", M_PI/2);
        sampler->addSample("π", M_PI);
        views[k].chart()->add(scales[k]);
        views[k].show();
    }
    return app.exec();
}
