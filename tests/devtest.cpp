#include <QApplication>
#include <Ksl/Chart.h>
#include <Ksl/Csv.h>
#include <Ksl/LineRegr.h>
using namespace Ksl;

#include <iostream>
using namespace std;


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Chart chart;

    auto DATA = Csv("ex1data1.txt", false, ',').matrix();

    auto x = getcol(DATA, 0);
    auto y = getcol(DATA, 1);

    auto a = LineRegr(x, y).result();

    chart.plot("data", x, y, "rc");
    chart.line("fit", a[0], a[1], "bl");

    chart.show();
    return app.exec();
}
