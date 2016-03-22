#include <QApplication>
#include <QDebug>

#include <iostream>
using namespace std;

#include <Ksl/ChartWindow.h>
#include <Ksl/MultiLinearRegr.h>
using namespace Ksl;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ChartWindow chart;
    chart.xyScale()->axis(XYScale::LeftAxis)
        ->setName("BUILDING VALUES");
    chart.xyScale()->axis(XYScale::BottomAxis)
        ->setName("SAMPLE ORDER");


    // File containing data
    Csv csv("housing.data");

    // Y values from training set
    auto y = csv.array("MEDV");

    // X values from training set
    Array<2> X(csv.rows(), 8);
    QList<Array<1>> xi;
    // Use variables
    // LSTAT NOX RM AGE DIS RAD PTRATIO
    xi.append(csv.array("LSTAT"));
    xi.append(csv.array("NOX"));
    xi.append(csv.array("RM"));
    xi.append(csv.array("AGE"));
    xi.append(csv.array("DIS"));
    xi.append(csv.array("RAD"));
    xi.append(csv.array("PTRATIO"));
    X.setCol(0, 1.0);
    for (int k=1; k<8; k++)
        X.setCol(k, xi[k-1]);

    MultiLinearRegr regr(X, y);

    // create series of predicted values
    auto c = regr.result();
    auto y_fit = samesize(y);
    for (int k=0; k<y_fit.size(); k++) {
        double yk = c[0];
        for (int l=1; l<c.size(); l++)
            yk += c[l] * xi[l-1][k];
        y_fit[k] = yk;
    }


    // plot comparison
    auto x = linspace(0.0, double(y.size()));
    chart.xyPlot("value", x, y, XYPlot::Line, Qt::blue);
    chart.xyPlot("fit value", x, y_fit, XYPlot::Line, Qt::red);

    chart.show();
    return app.exec();
}
