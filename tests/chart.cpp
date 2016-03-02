
#include <QApplication>
#include <Ksl/ChartWindow.h>
#include <Ksl/Regression/Linear.h>
#include <iostream>

using namespace std;
using namespace Ksl;
using namespace Ksl::Regression;

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

    // result[0] is the linear coefficient and
    // result[1] is the angular coefficient
    cout << "fitting line is y = " << result[1]
         << " x + " << result[0] << endl;

    // plot data and fitting line
    chart.xyPlot("data", vx, vy, XYPlot::Circles, Qt::blue, Qt::green);
    chart.xyPlot("regression", vx, vr, XYPlot::Line, Qt::red);

    chart.show();
    return app.exec();
}
