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
        ->setName("SAMPLE ORDER");


    Csv csv("housing.data");

    auto value = csv.array("MEDV");
    value /= max(value);

    auto crime = csv.array("CRIM");
    crime /= max(crime);

    auto rooms = csv.array("RM");
    rooms /= max(rooms);

    auto x = linspace(0.0, double(value.size()));
    chart.xyPlot("crime", x, crime, XYPlot::Line, Qt::red);
    chart.xyPlot("rooms", x, rooms, XYPlot::Line, Qt::green);
    chart.xyPlot("value", x, value, XYPlot::Circles, Qt::blue);

    chart.show();
    return app.exec();
}
