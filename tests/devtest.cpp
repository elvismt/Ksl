#include <QApplication>
#include <Ksl/Chart.h>
using namespace Ksl;


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Chart chart;

    chart.plot(randspace(5000), "kor");

    chart.show();
    return app.exec();
}
