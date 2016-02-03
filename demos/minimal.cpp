
#include <QApplication>
#include <QSL/FigureWidget.h>
#include <QSL/LinearScale.h>
#include <QSL/SimpleSeries.h>
#include <QSL/Random.h>
#include <QSL/LinearRegression.h>
using namespace QSL;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Random rand;

    const int ptCount = 20;
    const double step = 2.0*PI/ptCount;
    Array1D<double> x(ptCount), y(ptCount), yFit;

    // simulate data
    for (int k=0; k<ptCount; ++k) {
        x[k] = -PI + k*step;
        y[k] = ( 8.0 + 3.0*x[k] ) + rand.nextFloat(4.0)-2.0;
    }

    // create linear regression
    auto params = LinearRegression::exec(x, y);
    yFit = x.copy();
    yFit *= params[1];
    yFit += params[0];

    SimpleSeries dataSeries("data", x, y, QPen(Qt::black), QBrush(Qt::blue));
    SimpleSeries fitSeries("regression", x, yFit, QPen(Qt::red), Qt::NoBrush, SimpleSeries::Line);

    LinearScale scale;
    scale.add(dataSeries);
    scale.add(fitSeries);

    FigureWidget figure;
    figure.figure()->add(scale);
    figure.show();
    return app.exec();
}
