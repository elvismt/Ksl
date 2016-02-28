
#include <QApplication>
#include <Ksl/ChartWindow.h>

using namespace Ksl;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ChartWindow chart;

    auto Vx = linspace(-M_PI, M_PI, 0.2);

    auto Vy = applied([](double x) {
        return cos(x) + 0.5*sin(6*x)*cos(2*x);
    }, Vx);

    chart.xyPlot(Vx, cos(Vx), XYPlot::Squares, "Cos(X)", Qt::green);
    chart.xyPlot(Vx, Vy, XYPlot::Circles, "Wave(X)", Qt::blue);

    chart.show();
    return app.exec();
}
