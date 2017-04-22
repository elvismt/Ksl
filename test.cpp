#include <QApplication>
#include <QDebug>
#include <ksl/plot/FigureView.h>
#include <ksl/random/Normal.h>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    // figure and view widget
    ksl::plot::FigureView figureView;
    ksl::plot::Figure *figure = figureView.figure();

    // add scale
    ksl::plot::LinearScale scale("Scale", figure);

    // create some data
    const int64_t pointCount = 300;
    ksl::random::Normal distribution1(0.0, 0.8);
    ksl::random::Normal distribution2(2.0, 0.4);
    QVector<double> x1(pointCount), y1(pointCount);
    QVector<double> x2(pointCount), y2(pointCount);
    for (int64_t k=0; k<pointCount; ++k) {
        x1[k] = distribution1();
        y1[k] = distribution1();
        x2[k] = distribution2();
        y2[k] = distribution2();
    }

    // create series plots
    ksl::plot::Series plot1(x1, y1, "kor");
    scale.addItem(&plot1);
    ksl::plot::Series plot2(x2, y2, "kob");
    scale.addItem(&plot2);

    // show the window and run app
    figureView.show();
    return app.exec();
}
