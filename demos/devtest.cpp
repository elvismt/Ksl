#include <QApplication>
#include <QtGui>
#include <QDebug>

#include <Ksl/Array.h>
#include <Ksl/Graph.h>
#include <Ksl/Canvas.h>
using namespace Ksl;

#include <iostream>
using namespace std;


class MyCanvas: public Canvas
{
    void paint(QPainter *painter, const QRect &rect) {
        painter->drawText(30, 30, "Hello Canvas");
    }

    void leftClick(const QPoint &pos) {
        qDebug() << "clicked at" << pos;
    }

    void rightClick(const QPoint &pos) {
        qDebug() << "right clicked at" << pos;
    }
};


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MyCanvas canvas;
    canvas.show();
    return app.exec();
}
