#include <QApplication>
#include <Ksl/Chart.h>
#include <QHash>

using namespace Ksl;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Chart chart;

    auto x_model = linspace(-2*M_PI, 2*M_PI, 0.2);

    auto x_data1 = linspace(-2*M_PI, 2*M_PI, 1.1);
    auto y_data1 = sin(x_data1);
    for (auto &yi : y_data1)
        yi += double(rand())/RAND_MAX *0.3;

    auto x_data2 = linspace(-2*M_PI, 2*M_PI, 1.1);
    auto y_data2 = cos(x_data2);
    for (auto &yi : y_data2)
        yi += double(rand())/RAND_MAX *0.3;


    chart.plot(x_model, sin(x_model), "b-");
    chart.plot(x_data1, y_data1, "ro");
    chart.plot(x_data2, y_data2, "ko");

    chart.show();
    return app.exec();
}
