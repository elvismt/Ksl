#include <QApplication>
#include <Ksl/Chart.h>
using namespace Ksl;


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Chart chart;

    chart.plot(randspace(100), "kor");
    chart.plot(randspace(100), "b-");

    chart.show();
    return app.exec();
}
