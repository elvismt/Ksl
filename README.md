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

# CODE SAMPLE

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
        
        auto Vx = linspace(-2*M_PI, 2*M_PI, 0.2);
        
        chart.xyPlot("Cos(X)", Vx, cos(Vx), XYPlot::Line, Qt::blue);
        QPen pen(Qt::blue);
        pen.setWidth(2);
        chart.xyPlot("Cos(X)")->setPen(pen);
        
        // apply lambda to array
        auto Vwave = applied([](double x) {
            return cos(x) + 0.5*sin(3*x);
        }, Vx);
        
        chart.xyPlot("Wave(X)", Vx, Vwave, XYPlot::AreaUnder, Qt::red);
        QBrush brush(QColor(255,0,0,100));
        chart.xyPlot("Wave(X)")->setBrush(brush);
        
        chart.show();
        return app.exec();
    }

It gives you

    ![](https://github.com/elvismt/Ksl/blob/master/tests/chart2.png)

If you are looking for a C/Gtk solution for 2D visualization. Take a look
at [slope](https://github.com/elvismt/slope)
