
TEMPLATE = app
TARGET = QSL_test
INCLUDEPATH += ./ src/
CONFIG += c++11
QT += widgets

# Input
HEADERS += src/QSL/Figure.h \
           src/QSL/FigurePrivate.h \
           src/QSL/FigureScale.h \
           src/QSL/FigureScalePrivate.h \
           src/QSL/FigureWidget.h \
           src/QSL/FigureWidgetPrivate.h \
           src/QSL/Global.h \
           src/QSL/Object.h \
           src/QSL/ObjectPrivate.h \
    src/QSL/LinearScale.h \
    src/QSL/LinearScalePrivate.h \
    src/QSL/FigureItem.h \
    src/QSL/FigureItemPrivate.h

SOURCES += src/QSL/Figure.cpp \
           src/QSL/FigureScale.cpp \
           src/QSL/FigureWidget.cpp \
           src/QSL/test.cpp \
    src/QSL/LinearScale.cpp \
    src/QSL/FigureItem.cpp
