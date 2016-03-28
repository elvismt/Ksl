KSL
===

KSL is a free (LGPL3) C++/Qt library with utilities for science. Our goal
is to provide tools to facilitade and make fast the development of programs
for data analisys and information retrieval. We start with simple array
handling and linear regression as well as a fast and featureful chart
widget for visualization.

KSL's (growing) list of current features is:

   * Data Visualization Widgets
   * Advanced Data Structures
   * Regression Engines

The numerical routines used Ksl classes are primarily from the Mighty GNU
Scientific Library [GSL](http://www.gnu.org/software/gsl)
We thank and congratulate it's developers for the great work. Ksl follows
some of KDE's software design goals and all of it's philosophy but it is
not an official KDE component.

# PLOTTING

The following minimal code

    #include <QApplication>
    #include <Ksl/Chart.h>

    using namespace Ksl;

    int main(int argc, char *argv[]) {
        QApplication app(argc, argv);
        Chart chart;

        auto x = linspace(-2*M_PI, 2*M_PI, 0.2);
        chart.plot("Cos(X)", x, cos(x), "bl");

        chart.show();
        return app.exec();
    }

produces a chart similar to the following

 ![](https://github.com/elvismt/Ksl/blob/master/tests/chart1.png)


# REGRESSION

 
Whith the following program predits building values at boston city from
a set of known parameters by using a linear regression

	#include <QApplication>
	#include <QDebug>

	#include <Ksl/Chart.h>
	#include <Ksl/Csv.h>
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
		chart.plot("value", x, y_data, "bl");
		chart.plot("fit value", x, y_model, "rl");

		chart.show();
		return app.exec();
	}

The result is the following:

 ![](https://github.com/elvismt/Ksl/blob/master/tests/regression.png)

If you are looking for a C/Gtk solution for 2D visualization. Take a look
at [slope](https://github.com/elvismt/slope)
