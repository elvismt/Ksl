#include <QApplication>
#include <ksl/plot/FigureView.h>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    // view widget
    ksl::plot::FigureView figureView;

    // add scales
    ksl::plot::LinearScale scale1;
    scale1.setLayoutRect(QRectF(0,0,1,1));
    figureView.figure()->addScale(&scale1);
    ksl::plot::LinearScale scale2;
    scale2.setLayoutRect(QRectF(0,1,1,1));
    figureView.figure()->addScale(&scale2);

    figureView.show();
    return app.exec();
}
