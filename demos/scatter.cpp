#include <QApplication>
#include <Ksl/ChartView.h>
#include <Ksl/ChartLinscale.h>
#include <Ksl/SeriesPlot.h>
#include <Ksl/ChartAxis.h>
using namespace Ksl;


int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    ChartView view("BOXED PARTICLES");
    ChartLinscale scale;

    scale.add(new SeriesPlot(
                  randspace(2000, 1000.0),
                  randspace(2000, 1000.0),
                  "Scatter", Qt::blue,
                  SeriesPlot::Circles));

    scale.showAxis(BottomAxis|LeftAxis|TopAxis|RightAxis);
    auto sampler = scale.axis(BottomAxis)->sampler();
    sampler->addSample("0", 0.0);
    sampler->addSample("L/2", 500.0);
    sampler->addSample("L", 1000.0);
    sampler = scale.axis(LeftAxis)->sampler();
    sampler->addSample("0", 0.0);
    sampler->addSample("L/2", 500.0);
    sampler->addSample("L", 1000.0);

    view.chart()->setColorTheme(Chart::DarkTheme);
    view.chart()->add(scale);
    view.show();

    return app.exec();
}
