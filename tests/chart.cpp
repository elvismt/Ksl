
#include <QApplication>
#include <Ksl/ChartWindow.h>

using namespace Ksl;


double wave1(double x) {
    return sin(x) + 0.2*cos(5*x);
}

double wave2(double x) {
    return cos(x) + 0.2*sin(5*x);
}


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ChartWindow chart("Waves");

    auto x = linspace(0.0, 4*M_PI, 0.1);
    auto y1 = applied(wave1, x);
    auto y2 = applied(wave2, x);

    chart.xyPlot("Wave1", x, y1, XYPlot::Line, Qt::red);
    chart.xyPlot("Wave2", x, y2, XYPlot::Line, Qt::blue);

    chart.show();
    return app.exec();
}
