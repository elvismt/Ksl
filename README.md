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

# DEMOS

The figures below were created with KSL's widgets:

   * A representation of data indexed in a quad-tree

![](https://github.com/elvismt/Ksl/blob/devel/tests/quadtree.png)

   * We are working in a chart engine (soon it will have axis)

![](https://github.com/elvismt/Ksl/blob/devel/tests/chart.png)

# CODE SAMPLE

The code for this chart is as simple as

    #include <QApplication>
    #include <Ksl/ChartWindow.h>

    using namespace Ksl;

    int main(int argc, char *argv[]) {
        QApplication app(argc, argv);
        ChartWindow chart;
        
        auto x = linspace(-M_PI, M_PI, 0.01);
        
        chart.xyPlot(x, cos(x), "Cos(X)", Qt::blue);
        
        chart.show();
        return app.exec();
    }

If you are looking for a C/Gtk solution for 2D visualization. Take a look
at [slope](https://github.com/elvismt/slope)
