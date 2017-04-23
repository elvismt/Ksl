#include <QApplication>
#include <QDebug>
#include <ksl/plot/Chart.h>
#include <ksl/random/Normal.h>

using namespace ksl;

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    plot::Chart chart;

    // create some random data
    const int64_t pointCount = 300;
    ksl::random::Normal distribution1(0.0, 0.8);
    ksl::random::Normal distribution2(2.0, 0.4);
    QVector<double> x1(pointCount), y1(pointCount);
    QVector<double> x2(pointCount), y2(pointCount);
    for (int64_t k=0; k<pointCount; ++k) {
        x1[k] = distribution1();
        y1[k] = distribution1();
        x2[k] = distribution2();
        y2[k] = distribution2();
    }

    chart.series(x1, y1, "bOr");
    chart.series(x2, y2, "kOg");

    chart.show();
    return app.exec();
}
