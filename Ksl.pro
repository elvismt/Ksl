
TEMPLATE = app
TARGET = Ksl
INCLUDEPATH += ./ src/
greaterThan(QT_MAJOR_VERSION, 4) {
    CONFIG += c++11
    QT += widgets
}
lessThan(QT_MAJOR_VERSION, 5) {
    QMAKE_CXXFLAGS += -std=c++11
}

# Input
HEADERS += \
    src/Ksl/Array.h \
    src/Ksl/CanvasWindow.h \
    src/Ksl/CanvasWindow_p.h \
    src/Ksl/Figure.h \
    src/Ksl/Figure_p.h \
    src/Ksl/FigureItem.h \
    src/Ksl/FigureItem_p.h \
    src/Ksl/FigureScale.h \
    src/Ksl/FigureScale_p.h \
    src/Ksl/Global.h \
    src/Ksl/Math.h \
    src/Ksl/Object.h \
    src/Ksl/Object_p.h \
    src/Ksl/ChartWindow.h \
    src/Ksl/ChartWindow_p.h \
    src/Ksl/XYScale.h \
    src/Ksl/XYScale_p.h \
    src/Ksl/XYPlot.h \
    src/Ksl/XYPlot_p.h \
    src/Ksl/XYAxis.h \
    src/Ksl/XYAxis_p.h \
    src/Ksl/XYAxisSampler_p.h \
    src/Ksl/XYAxisSampler.h \
    src/Ksl/FigureWidget.h \
    src/Ksl/FigureWidget_p.h \
    src/Ksl/Regression/Linear.h \
    src/Ksl/Regression/Linear_p.h

SOURCES += \
    tests/chart.cpp \
    src/Ksl/CanvasWindow.cpp \
    src/Ksl/Figure.cpp \
    src/Ksl/FigureItem.cpp \
    src/Ksl/FigureScale.cpp \
    src/Ksl/ChartWindow.cpp \
    src/Ksl/XYScale.cpp \
    src/Ksl/XYPlot.cpp \
    src/Ksl/XYAxis.cpp \
    src/Ksl/XYAxisSampler.cpp \
    src/Ksl/FigureWidget.cpp \
    src/Ksl/Regression/Linear.cpp

RESOURCES += \
    src/qrc/Icons.qrc
