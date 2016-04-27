#include <QApplication>
#include <Ksl/Chart.h>
#include <QHash>

using namespace Ksl;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Chart chart;

    chart.plot(randspace(100), randspace(100), "kor");

    chart.show();
    return app.exec();
}

