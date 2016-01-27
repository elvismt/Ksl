
#include <QApplication>
#include <QSL/FigureWidget.h>
#include <QSL/LinearScale.h>
#include <QSL/SimpleSeries.h>
#include <QDebug>
using namespace QSL;


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    const int ptCount = 500;
    const double step = 2.0*PI/ptCount;
    Array1D<double> x(ptCount), y1(ptCount), y2(ptCount);
    for (int k=0; k<ptCount; ++k) {
        x[k] = -PI + k*step;
        y1[k] = sin(x[k]) + double(rand())/RAND_MAX;
        y2[k] = cos(x[k]) + double(rand())/RAND_MAX;
    }

    SimpleSeries sineSeries("sine", x, y1, QPen(Qt::black), QBrush(Qt::blue));
    SimpleSeries cossineSeries("sine", x, y2, QPen(Qt::black), QBrush(Qt::red));

    LinearScale scale;
    scale.add(sineSeries);
    scale.add(cossineSeries);

    FigureWidget figure;
    figure.figure()->add(scale);
    figure.show();
    return app.exec();
}
