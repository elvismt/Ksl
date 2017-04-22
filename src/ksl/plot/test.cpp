#include <QApplication>
#include <ksl/plot/FigureView.h>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    // figure and view widget
    ksl::plot::FigureView figureView;
    ksl::plot::Figure *figure = figureView.figure();

    // add scales
    ksl::plot::LinearScale scale1("Scale 1", figure);
    scale1.setLayoutRect(QRectF(0,0,1,1));
    ksl::plot::LinearScale scale2("Scale 2", figure);
    scale2.setLayoutRect(QRectF(0,1,1,1));

    figureView.show();
    return app.exec();
}
