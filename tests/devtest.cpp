#include <QApplication>
#include <QDebug>
#include <Ksl/ChartWindow.h>
#include <Ksl/Functions.h>

using namespace Ksl;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ChartWindow chart;

    // polynomial: y = 2*x^2 + 4*x^3 + 3*x^4 - x^5
    Array<1> a = { 0.0, 0.0, 2.0, 4.0, 3.0, - 1.0 };

    chart.poly("polynomial", a, -3, 5, Qt::blue);

    chart.show();
    return app.exec();
}
