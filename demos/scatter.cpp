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
    scale.add(new SeriesPlot(randspace(2000, 1000.0), randspace(2000, 1000.0)));

    ChartView view("2000 Scattered dots");
    view.chart()->add(scale);
    view.show();

    return app.exec();
}
