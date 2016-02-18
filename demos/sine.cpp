#include <QApplication>
#include <Ksl/ChartView.h>
#include <Ksl/ChartLinscale.h>
#include <Ksl/SeriesPlot.h>
using namespace Ksl;

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    auto x = linspace(0.0, 12.6, 0.3);
    auto y = sin(x);

    ChartLinscale scale;
    scale.add(new SeriesPlot(x, y, SeriesPlot::Line, Qt::blue));

    ChartView view("Sin(X) function");
    view.chart()->add(scale);
    view.show();

    return app.exec();
}
