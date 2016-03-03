
#include <QApplication>
#include <Ksl/ChartWindow.h>
#include <Ksl/LinRegr.h>
#include <iostream>

using namespace std;
using namespace Ksl;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ChartWindow chart("Linear Regression");

    // emulate noisy data
    auto vx = linspace(0.0, 100.0);
    auto vy = vx * 2.3;
    vy += 20.0;
    for (auto &y : vy)
        y += -25.0 + 50.0*double(rand())/RAND_MAX;

    // create solver and perform regression
    LinRegr regr(vx, vy);
    regr.solve();

    // construct array with the fitting line
    auto result = regr.result();
    auto vr = vx * result[1];
    vr += result[0];

    // plot data and fitting line
    chart.xyPlot("Data", vx, vy, XYPlot::Circles, Qt::black, Qt::green);
    chart.xyPlot("Fitted line", vx, vr, XYPlot::Line, Qt::blue);

    chart.show();
    return app.exec();
}
