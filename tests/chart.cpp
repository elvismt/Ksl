#include <QApplication>
#include <Ksl/Chart.h>
#include <iostream>

using namespace Ksl;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Chart chart;

    chart.plot(randspace(500), randspace(500), "kog");

    chart.show();
    return app.exec();
}
