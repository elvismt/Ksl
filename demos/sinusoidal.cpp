
#include <QApplication>
#include <Ksl/Chart.h>
using namespace Ksl;

int main(int argc, char *argv[])
{
    QApplication app(argc,argv);

    auto x = linspace(-M_PI, M_PI, 0.05);
    Chart charts[2];
    ChartLinscale *scales[2];

    // Add sme functions
    scales[0] = charts[0].addScale("sine-scale");
    scales[0]->add(new SeriesPlot(x, sin(x), "Sin(X)", Qt::red));
    charts[0].setWindowTitle("SIN");
    // identify function maxima and zeros
    scales[0]->add(new ChartLabel("zero", -M_PI, 0.0));
    scales[0]->add(new ChartLabel("zero", 0.0, 0.0));
    scales[0]->add(new ChartLabel("zero", M_PI, 0.0));
    scales[0]->add(new ChartLabel("minimum", -M_PI/2, -1.0));
    scales[0]->add(new ChartLabel("maximum", M_PI/2, 1.0));

    scales[1] = charts[1].addScale("cossine-scale");
    scales[1]->add(new SeriesPlot(x, cos(x), "Cos(X)", Qt::green));
    charts[1].setWindowTitle("COS");

    for (int k=0; k<2; ++k) {
        // We will use custom axis labels, in terms of pi
        auto sampler = scales[k]->axis(X_Axis)->sampler();
        sampler->addSample("-π", -M_PI);
        sampler->addSample("-π/2", -M_PI/2);
        sampler->addSample("π/2", M_PI/2);
        sampler->addSample("π", M_PI);
        charts[k].show();
    }
    return app.exec();
}
