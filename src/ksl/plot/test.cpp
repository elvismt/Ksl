#include <QApplication>
#include <ksl/plot/FigureView.h>

int main(int argc, char **argv) {
    QApplication app(argc, argv);

    ksl::plot::FigureView figureView;
    figureView.show();

    return app.exec();
}
