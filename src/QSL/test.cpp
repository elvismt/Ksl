
#include <QApplication>
#include <QSL/FigureWidget.h>
using namespace QSL;


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    FigureWidget figure;
    figure.show();

    return app.exec();
}
