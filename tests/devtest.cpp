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
        ->setName("NORMALIZED VALUES");
    chart.xyScale()->axis(XYScale::BottomAxis)
        ->setName("SAMPLE OERDER");

    Csv csv("housing.data");
    auto matrix = csv.asMatrix();

    auto value = getcol(matrix, 13);
    value /= max(value);

    auto crime = getcol(matrix, 0);
    crime /= max(crime);

    auto rooms = getcol(matrix, 5);
    rooms /= max(rooms);

    auto x = linspace(0.0, double(crime.size()));

    chart.xyPlot("crime", x, crime, XYPlot::Line, Qt::red);
    chart.xyPlot("rooms", x, rooms, XYPlot::Line, Qt::green);
    chart.xyPlot("value", x, value, XYPlot::Circles, Qt::blue);

    chart.show();
    return app.exec();
}
