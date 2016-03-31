#include <QApplication>
#include <Ksl/Chart.h>

using namespace Ksl;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Chart chart;

    auto x = linspace(-2*M_PI, 2*M_PI, 0.2);

    chart.plot("Sin(X)", x, sin(x), "bl");
    chart.poly("p(x)", { 1./20., 0, 1./20. }, -2*M_PI, 2*M_PI);

    chart.show();
    return app.exec();
}
