
#include <QApplication>
#include <Ksl/ChartWindow.h>

using namespace Ksl;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ChartWindow chart;

    auto Vx = linspace(-2*M_PI, 2*M_PI, 0.2);

    auto Vy = applied([](double x) {
        return cos(x) + 0.5*sin(7*x);
    }, Vx);

    chart.xyPlot("Wave(X)", Vx, Vy, XYPlot::Circles, Qt::blue);
    chart.xyPlot("Cos(X)", Vx, cos(Vx), XYPlot::Line, Qt::red);

    chart.show();
    return app.exec();
}

