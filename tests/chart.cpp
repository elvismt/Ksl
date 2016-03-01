
#include <QApplication>
#include <Ksl/ChartWindow.h>

using namespace Ksl;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ChartWindow chart;
    chart.xyScale()->axis(XYScale::BottomAxis)->setName("PHASE");
    chart.xyScale()->axis(XYScale::LeftAxis)->setName("AMPLITUDE");

    auto Vx = linspace(-2*M_PI, 2*M_PI, 0.2);

    chart.xyPlot("Cos(X)", Vx, cos(Vx), XYPlot::Line, Qt::blue);
    QPen pen(Qt::blue);
    pen.setWidth(2);
    chart.xyPlot("Cos(X)")->setPen(pen);

    auto Vwave = applied([](double x) {
        return cos(x) + 0.5*sin(7*x);
    }, Vx);
    chart.xyPlot("Wave(X)", Vx, Vwave, XYPlot::AreaUnder, Qt::red);
    QBrush brush(QColor(255,0,0,100));
    chart.xyPlot("Wave(X)")->setBrush(brush);

    auto Vsin = applied([](double x) {
        return 0.25*sin(x) + 1.5;
    }, Vx);
    chart.xyPlot("Sin(X)/2", Vx, Vsin,
        XYPlot::Circles, Qt::black, Qt::green);

    chart.show();
    return app.exec();
}
