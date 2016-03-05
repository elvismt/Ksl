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

The numerical routines in Ksl are primarily adapted from the Mighty GNU
Scientific Library [GSL](http://www.gnu.org/software/gsl)
We thank and congratulate it's developers for the great work. Ksl follows
some of KDE's software design goals and all of it's philosophy but it is
not an official KDE component.

# PLOTTING

The following minimal code

    #include <QApplication>
    #include <Ksl/ChartWindow.h>

    using namespace Ksl;

    int main(int argc, char *argv[]) {
        QApplication app(argc, argv);
        ChartWindow chart;
        
        auto x = linspace(-2*M_PI, 2*M_PI, 0.2);
        chart.xyPlot("Cos(X)", x, cos(x));
        
        chart.show();
        return app.exec();
    }

produces a chart similar to the following

 ![](https://github.com/elvismt/Ksl/blob/master/tests/chart1.png)

And you can make more elaborate ones with code like
    
    #include <QApplication>
    #include <Ksl/ChartWindow.h>
    
    using namespace Ksl;
    
    int main(int argc, char *argv[]) {
        QApplication app(argc, argv);
        ChartWindow chart;
        
        auto x = linspace(-2*M_PI, 2*M_PI, 0.2);
        
        chart.xyPlot("Sin(X)", x, sin(x), XYPlot::AreaUnder, Qt::blue);
        QBrush sinBrush(QColor(0,0,255,100));
        chart.xyPlot("Sin(X)")->setBrush(sinBrush);
        
        chart.xyPlot("Cos(X)", x, cos(x), XYPlot::AreaUnder, Qt::red);
        QBrush cosBrush(QColor(255,0,0,100));
        chart.xyPlot("Cos(X)")->setBrush(cosBrush);
        
        chart.show();
        return app.exec();
    }

It gives you

 ![](https://github.com/elvismt/Ksl/blob/master/tests/chart2.png)
 
# REGRESSION

Whith the following program you can fit a strait line to a series of
numerical data

    #include <QApplication>
    #include <Ksl/ChartWindow.h>
    #include <Ksl/LinReg.h>

    using namespace Ksl;

    int main(int argc, char *argv[]) {
        QApplication app(argc, argv);
        ChartWindow chart("Linear Regression");
        
        // emulate noisy data
        auto vx = linspace(0.0, 100.0);
        auto vy = vx * 2.3;
        vy += 20.0;
        for (auto &y : vy)
            y += -25.0 + 50.0*double(rand())/RAND_MAX;
        
        // create solver and perform regression
        LinRegr regr(vx, vy);
        regr.solve();
        
        // plot data and fitting line
        chart.xyPlot("Data", vx, vy, XYPlot::Circles, Qt::black, Qt::green);
        // plot fitting line
        chart.line("Fitted line", regr.result()[0], regr.result()[1], QPen(Qt::red));
        // plot a fancy text label
        chart.textLabel("KSL Rocks!", QPointF(30,150), Qt::red, 32.0);
        
        chart.show();
        return app.exec();
    }

It gives you

 ![](https://github.com/elvismt/Ksl/blob/master/tests/regression.png)
 
# VISUALIZE SCIENTIFIC DATA
 
The following is a plot of an X-Ray diffraction experiment.

![](https://github.com/elvismt/Ksl/blob/master/tests/diffraction.png)

Code:

    #include <QApplication>
    #include <Ksl/ChartWindow.h>
    #include <QFile>
    #include <QTextStream>

    using namespace Ksl;


    int main(int argc, char *argv[]) {
        QApplication app(argc, argv);
        ChartWindow chart("X-Ray Diffraction Data");
        
        QFile file("diffraction.dat");
        QTextStream stream(&file);
        Array<1> x(8501), y(8501);
        
        file.open(QIODevice::Text|QIODevice::ReadOnly);
        for (uint k=0; k<x.size(); ++k)
            stream >> x[k] >> y[k];
        file.close();
        
        // normalize to y_max = 1.0
        y /= max(y);
        
        chart.xyPlot("X-Ray diffraction", x, y);
        chart.show();
        
        return app.exec();
    }


If you are looking for a C/Gtk solution for 2D visualization. Take a look
at [slope](https://github.com/elvismt/slope)
