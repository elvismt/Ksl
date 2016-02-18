#include <QApplication>
#include <Ksl/ChartView.h>
#include <Ksl/ChartLinscale.h>
#include <Ksl/SeriesPlot.h>
#include <Ksl/Math.h>
using namespace Ksl;

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    auto x = linspace(0.0, 12.58, 0.3);
    SeriesPlot plot(x, apply(Math::sin, x), SeriesPlot::Line, Qt::blue);

    ChartLinscale scale;
    scale.add(plot);

    ChartView view("Sin(X) function");
    view.chart()->add(scale);
    view.show();

    return app.exec();
}
