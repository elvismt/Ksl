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

    scale.axis(X_Axis)->sampler()->setSamples({
        { "300", 300.0 },
        { "600", 600.0 },
        { "1000", 1000.0 }
    });

    scale.axis(Y_Axis)->sampler()->setSamples({
        { "300", 300.0 },
        { "600", 600.0 },
        { "1000", 1000.0 }
    });

    ChartView view("2000 Scattered dots");
    view.chart()->add(scale);
    view.show();

    return app.exec();
}
