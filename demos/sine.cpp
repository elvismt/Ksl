#include <QApplication>
#include <Ksl/ChartView.h>
#include <Ksl/ChartLinscale.h>
#include <Ksl/SeriesPlot.h>
using namespace Ksl;

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    auto x = linspace(-M_PI, M_PI+0.1, 0.1);

    ChartLinscale scale2;
    scale2.add(new SeriesPlot(x, cos(x), "Cos(X)", Qt::red));
    ChartView view2("Cos(X)");
    view2.chart()->add(scale2);
    view2.show();

/*
    ChartLinscale scale1;
    scale1.add(new SeriesPlot(x, sin(x), "Sin(X)", Qt::blue));
    ChartView view1("Sin(X)");
    view1.chart()->add(scale1);
    view1.show();

    ChartLinscale scale3;
    scale3.add(new SeriesPlot(x, tan(x), "Tan(X)", Qt::green));
    ChartView view3("Tan(X)");
    view3.chart()->add(scale3);
    view3.show();
*/
    return app.exec();
}
