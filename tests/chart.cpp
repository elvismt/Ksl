
#include <QApplication>
#include <Ksl/ChartWindow.h>

using namespace Ksl;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ChartWindow chart;

    auto x = linspace(0.0, 2.0*M_PI, 0.2);
    chart.xyScale()->add(new XYPlot(x, sin(x), "Sin(X)", Qt::blue));
    chart.xyScale()->add(new XYPlot(x, cos(x), "Cos(X)", Qt::red));

    chart.show();
    return app.exec();
}
