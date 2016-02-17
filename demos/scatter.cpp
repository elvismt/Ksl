#include <QApplication>
#include <Ksl/ChartView.h>
#include <Ksl/ChartLinscale.h>
#include <Ksl/SeriesPlot.h>
#include <Ksl/ChartAxis.h>
using namespace Ksl;

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    auto x = randspace(2000, 1000.0);
    auto y = randspace(2000, 1000.0);
    
    SeriesPlot plot(x,y);
    ChartLinscale scale;
    scale.add(plot);

    ChartView view;
    view.chart()->add(scale);
    view.show();

    return app.exec();
}
