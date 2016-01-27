
#include <QApplication>
#include <QSL/FigureWidget.h>
#include <QSL/LinearScale.h>
using namespace QSL;


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    FigureWidget figure;
    LinearScale scale;
    figure.figure()->add(scale);
    figure.show();

    return app.exec();
}
