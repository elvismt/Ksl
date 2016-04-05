#include <QApplication>
#include <Ksl/Chart.h>
using namespace Ksl;


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Chart chart;

    chart.plot(randspace(100), "kor", "ramdom points");
    chart.plot(randspace(100), "b-", "ramdom line");

    chart.show();
    return app.exec();
}
