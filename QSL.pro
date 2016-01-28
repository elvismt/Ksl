
TEMPLATE = app
TARGET = QSL_test
INCLUDEPATH += ./ src/
CONFIG += c++11
QT += widgets


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
           src/QSL/FigureItemPrivate.h \
           src/QSL/SimpleSeries.h \
           src/QSL/Array1D.h \
           src/QSL/SimpleSeriesPrivate.h \
    src/QSL/ChartAxis.h \
    src/QSL/ChartAxisPrivate.h \
    src/QSL/Random.h \
    src/QSL/RandomPrivate.h

SOURCES += src/QSL/Figure.cpp \
           src/QSL/FigureScale.cpp \
           src/QSL/FigureWidget.cpp \
           src/QSL/LinearScale.cpp \
           src/QSL/FigureItem.cpp \
           src/QSL/SimpleSeries.cpp \
           demos/minimal.cpp \
    src/QSL/ChartAxis.cpp \
    src/QSL/Random.cpp
