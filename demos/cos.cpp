#include <QApplication>
#include <Ksl/ChartView.h>
#include <Ksl/ChartLinscale.h>
#include <Ksl/SeriesPlot.h>
using namespace Ksl;

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    auto x = linspace(-M_PI, M_PI, 0.1);

    ChartLinscale scale;
    scale.add(new SeriesPlot(x, cos(x), "Cos(X)", Qt::blue));

    auto sampler = scale.axis(X_Axis)->sampler();
    sampler->addSample("-π", -M_PI);
    sampler->addSample("-π/2", -M_PI/2);
    sampler->addSample("π/2", M_PI/2);
    sampler->addSample("π", M_PI);

    ChartView view("Cos(X)");
    view.chart()->add(scale);
    view.show();

    return app.exec();
}
