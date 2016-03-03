
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

    auto fig1 = chart.figure("fig1");
    auto fig2 = chart.figure("fig2");
    auto fig3 = chart.figure("fig3");

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
    XYScale scale1;
    fig1->add(&scale1);
    XYPlot plot1(vx, vy, XYPlot::Circles, "Data");
    scale1.add(&plot1);

    XYScale scale2;
    fig2->add(&scale2);
    XYPlot plot2(vx, vr, "Fitting Line", Qt::red);
    scale2.add(&plot2);

    XYScale scale3;
    fig3->add(&scale3);
    XYPlot plot3(vx, vy, XYPlot::Circles, "Data");
    XYPlot plot4(vx, vr, "Fitting Line", Qt::red);
    scale3.add(&plot3);
    scale3.add(&plot4);

    chart.show();
    return app.exec();
}
