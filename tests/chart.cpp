#include <QApplication>
#include <Ksl/Chart.h>
#include <QHash>

using namespace Ksl;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Chart chart;

    int numPts = 1000;
        auto x = randspace(numPts, 1.0);
        auto y = randspace(numPts, 1.0);

        Array<1> x1, y1, x2, y2;

        for (int k=0; k<numPts; ++k) {
            if (y[k] > (-x[k] + 1.0)) {
                x1.append(x[k]);
                y1.append(y[k]);
            } else {
                x2.append(x[k]);
                y2.append(y[k]);
            }
        }

        chart.plot(x1, y1, "ro");
        chart.plot(x2, y2, "bo");

    chart.show();
    return app.exec();
}
