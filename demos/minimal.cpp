
#include <QApplication>
#include <QSL/FigureWidget.h>
#include <QSL/LinearScale.h>
#include <QSL/SimpleSeries.h>
#include <QSL/Random.h>
#include <QSL/Integration.h>
using namespace QSL;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Random rand;

    const int ptCount = 500;
    const double step = 2.0*PI/ptCount;
    Array1D<double> x(ptCount), y1(ptCount), y2(ptCount);
    for (int k=0; k<ptCount; ++k) {
        x[k] = -PI + k*step;
        y1[k] = sin(x[k]) + rand.nextFloat(0.3)-0.15;
        y2[k] = cos(x[k]) + rand.nextFloat(0.3)-0.15;
    }

    SimpleSeries sineSeries("sine", x, y1, QPen(Qt::black), QBrush(Qt::blue));
    SimpleSeries cossineSeries("cossine", x, y2, QPen(Qt::black), QBrush(Qt::red));

    LinearScale scale;
    scale.add(sineSeries);
    scale.add(cossineSeries);

    FigureWidget figure;
    figure.figure()->add(scale);
    figure.show();
    return app.exec();
}
