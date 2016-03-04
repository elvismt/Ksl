#include <QFile>
#include <QTextStream>
#include <QApplication>

#include <Ksl/ChartWindow.h>
using namespace Ksl;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFile file("data.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream str(&file);

    uint size;
    str >> size;

    Array<1> x(size);
    Array<1> ys(size);
    Array<1> yc(size);

    for (uint k=0; k<x.size(); k++)
        str >> x[k] >> ys[k] >> yc[k];

    ChartWindow chart;
    chart.xyPlot("data.dat", x, ys);
    chart.show();

    return app.exec();
}
