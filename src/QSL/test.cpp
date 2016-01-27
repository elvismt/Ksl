
#include <QApplication>
#include <QSL/FigureWidget.h>
#include <QSL/LinearScale.h>
#include <QSL/SimpleSeries.h>
#include <QDebug>
using namespace QSL;


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    const int ptCount = 1000;
    Array1D<double> x(ptCount), y(ptCount);
    for (int k=0; k<ptCount; ++k) {
        x[k] = 10.0 * double(rand())/RAND_MAX;
        y[k] = 10.0 * double(rand())/RAND_MAX;
    }

    SimpleSeries series("random", x, y);
    LinearScale scale;
    scale.add(series);

    FigureWidget figure;
    figure.figure()->add(scale);
    figure.show();
    return app.exec();
}
