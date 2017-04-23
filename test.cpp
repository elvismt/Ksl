#include <QApplication>
#include <QDebug>
#include <ksl/plot/Chart.h>
#include <ksl/random/Normal.h>

using namespace ksl;

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    // create some random data and plot it
    const int64_t N = 300;
    random::Normal n1(0.0, 0.8);
    random::Normal n2(2.0, 0.4);

    auto x1 = n1(N);
    auto y1 = n1(N);
    auto x2 = n2(N);
    auto y2 = n2(N);

    plot::Chart chart;
    chart.series(x1, y1, "kog");
    chart.series(x2, y2, "kor");

    chart.show();
    return app.exec();
}
