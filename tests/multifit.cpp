#include <QApplication>
#include <QDebug>

#include <iostream>
using namespace std;

#include <Ksl/Chart.h>
#include <Ksl/MultiLineRegr.h>
using namespace Ksl;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Chart chart;
    chart.scale()->axis(XYScale::LeftAxis)
        ->setName("BUILDING VALUES");
    chart.scale()->axis(XYScale::BottomAxis)
        ->setName("SAMPLE ORDER");


    // File containing data
    auto DATA = Csv("housing.data").matrix();

    // Y values from training set
    auto y = getcol(DATA, 13);
    int N = DATA.rows();

    // indices of data columns to use as parameters
    Array<1,int> param = linspace<int>(0, 12);

    // fill matrix with params
    Array<2> X(N, param.size()+1);
    X.setcol(0, 1.0);
    for (int j=0; j<param.size(); ++j) {
        X.coltocol(j+1, DATA, param[j]);
    }

    // Perform regression
    auto c = MultiLineRegr(X, y).result();

    // create series of predicted values
    auto y_fit = samesize(y);
    for (int k=0; k<y_fit.size(); k++) {
        double yk = c[0];
        for (int l=1; l<c.size(); l++)
            yk += c[l] * DATA[k][param[l-1]];
        y_fit[k] = yk;
    }

    // plot comparison
    auto x = linspace(0.0, double(y.size()));
    chart.plot("value", x, y, "bo");
    chart.plot("fit value", x, y_fit, "r-");

    chart.show();
    return app.exec();
}
