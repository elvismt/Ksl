
#include <QApplication>
#include <Ksl/ChartWindow.h>
#include <Ksl/Regression/Linear.h>

using namespace Ksl;
using namespace Ksl::Regression;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    ChartWindow chart;

    // emulate noisy data
    auto vx = linspace(0.0, 200.0);
    auto vy = vx * 2.3;
    for (auto &x : vx)
        x += -10.0 + 20.0*double(rand())/RAND_MAX;

    // create solver and perform regression
    LinRegr regr(vx, vy);
    regr.solve();

    // construct array with the fitting line
    auto result = regr.result();
    auto vr = vx * result[1];
    vr += result[0];

    // result[0] is the linear coefficient and
    // result[1] is the angular coefficient
    qDebug() << "fitting line is x = a*x + b with a="
             << result[1] << "and b=" << result[0];

    // plot data and fitting line
    chart.xyPlot("data", vx, vy, XYPlot::Circles, Qt::blue, Qt::yellow);
    chart.xyPlot("regression", vx, vr, XYPlot::Line, Qt::red);

    chart.show();
    return app.exec();
}
