
#include <QApplication>
#include <QDebug>

#include <iostream>
using namespace std;

#include <Ksl/Chart.h>
#include <Ksl/Csv.h>
#include <Ksl/MultiLineRegr.h>
using namespace Ksl;


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Chart chart;
    chart.scale()->axisLabels(
        "Building Values",
        "Sample Order");

    // Open file containing data
    Csv csv("housing.data");
    if (csv.empty()) {
        cout << "CSV file not found";
        return -1;
    }

    // Perform regression
    MultiLineRegr regr(csv, linspace<int>(0, 12), 13);

    // create series of predicted values
    Array<1> y_data = csv.array(13);
    Array<1> y_model(y_data.size());

    for (int k=0; k<y_model.size(); k++)
        y_model[k] = regr.model(k);

    // plot comparison
    auto x = linspace(0.0, double(y_data.size()));
    chart.plot(x, y_data, "b-", "training set");
    chart.plot(x, y_model, "r-", "predicted value");

    chart.show();
    return app.exec();
}
