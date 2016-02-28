
#include <QApplication>
#include <Ksl/ChartWindow.h>

using namespace Ksl;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ChartWindow chart;

    auto Vx = linspace(-M_PI, M_PI, 0.01);

    auto Vy = applied([](double x) {
        return cos(x) + sin(6*x)*cos(2*x);
    }, Vx);

    chart.xyPlot(Vx, cos(Vx), "Sin(X)", Qt::red);
    chart.xyPlot(Vx, Vy, "Wave(X)", Qt::blue);

    chart.show();
    return app.exec();
}
