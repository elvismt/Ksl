#include <QApplication>
#include <Ksl/Chart.h>

using namespace Ksl;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Chart chart;

    auto x = linspace(-2*M_PI, 2*M_PI, 0.2);

    chart.plot(x, sin(x), "b-", "Sin(X)");

    chart.show();
    return app.exec();
}
