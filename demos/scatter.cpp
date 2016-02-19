#include <QApplication>
#include <Ksl/ChartView.h>
#include <Ksl/ChartLinscale.h>
#include <Ksl/SeriesPlot.h>
#include <Ksl/ChartAxis.h>
using namespace Ksl;

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    ChartLinscale scale;
    scale.add(new SeriesPlot(randspace(2000, 1000.0),
                             randspace(2000, 1000.0),
                             "Scatter", Qt::blue,
                             SeriesPlot::Circles));

    auto sampler = scale.axis(X_Axis)->sampler();
    sampler->addSample("L/2", 500.0);
    sampler->addSample("L", 1000.0);

    sampler = scale.axis(Y_Axis)->sampler();
    sampler->addSample("L/2", 500.0);
    sampler->addSample("L", 1000.0);

    ChartView view("2000 Scattered dots");
    view.chart()->add(scale);
    view.show();

    return app.exec();
}
