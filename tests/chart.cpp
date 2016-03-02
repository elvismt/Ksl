
#include <QApplication>
#include <Ksl/ChartWindow.h>

using namespace Ksl;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ChartWindow chart;

    auto x = linspace(-2*M_PI, 2*M_PI, 0.2);

    chart.xyPlot("Sin(X)", x, sin(x), XYPlot::Circles, Qt::blue);
    QBrush sinBrush(QColor(0,0,255,100));
    chart.xyPlot("Sin(X)")->setBrush(sinBrush);

    chart.xyPlot("Cos(X)", x, cos(x), XYPlot::AreaUnder, Qt::red);
    QBrush cosBrush(QColor(255,0,0,100));
    chart.xyPlot("Cos(X)")->setBrush(cosBrush);

    chart.show();
    return app.exec();
}
