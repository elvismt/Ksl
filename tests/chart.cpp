#include <QApplication>
#include <Ksl/Chart.h>
#include <iostream>

using namespace Ksl;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Chart chart;

    chart.plot(randspace(300), randspace(300), "kor");

    chart.show();
    return app.exec();
}
