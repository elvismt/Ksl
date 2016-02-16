TEMPLATE = app
TARGET = Ksl
QT += widgets
CONFIG += c++11
INCLUDEPATH += ./

HEADERS += \
    Ksl/Global.h \
    Ksl/Array1D.h \
    Ksl/Plot/Chart.h \
    Ksl/Object_p.h \
    Ksl/Object.h \
    Ksl/Plot/Chart_p.h \
    Ksl/Plot/ChartView.h \
    Ksl/Plot/ChartView_p.h

SOURCES += \
    Ksl/main.cpp \
    Ksl/Plot/Chart.cpp \
    Ksl/Plot/ChartView.cpp

