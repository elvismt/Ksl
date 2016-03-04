
TEMPLATE = app
TARGET = Ksl_test
greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
    CONFIG += c++11
}
lessThan(QT_MAJOR_VERSION, 5) {
    QMAKE_CXXFLAGS += -std=c++11
}

DEPENDPATH += \
    tests \
    src/QRC \
    src/Core/Ksl \
    src/Plotting/Ksl \
    src/Regression/Ksl

INCLUDEPATH += \
    src/Core \
    src/Plotting \
    src/Regression

HEADERS += \
    src/Core/Ksl/Array.h \
    src/Core/Ksl/Global.h \
    src/Core/Ksl/Math.h \
    src/Core/Ksl/Object.h \
    src/Core/Ksl/Object_p.h \
    src/Core/Ksl/MemoryPool.h \
    src/Core/Ksl/MemoryPool_p.h \
    src/Core/Ksl/Graph.h \
    src/Plotting/Ksl/CanvasWindow.h \
    src/Plotting/Ksl/CanvasWindow_p.h \
    src/Plotting/Ksl/ChartWindow.h \
    src/Plotting/Ksl/ChartWindow_p.h \
    src/Plotting/Ksl/Figure.h \
    src/Plotting/Ksl/Figure_p.h \
    src/Plotting/Ksl/FigureItem.h \
    src/Plotting/Ksl/FigureItem_p.h \
    src/Plotting/Ksl/FigureScale.h \
    src/Plotting/Ksl/FigureScale_p.h \
    src/Plotting/Ksl/FigureWidget.h \
    src/Plotting/Ksl/FigureWidget_p.h \
    src/Plotting/Ksl/XYAxis.h \
    src/Plotting/Ksl/XYAxis_p.h \
    src/Plotting/Ksl/XYAxisSampler.h \
    src/Plotting/Ksl/XYAxisSampler_p.h \
    src/Plotting/Ksl/XYPlot.h \
    src/Plotting/Ksl/XYPlot_p.h \
    src/Plotting/Ksl/XYScale.h \
    src/Plotting/Ksl/XYScale_p.h \
    src/Regression/Ksl/LinRegr.h \
    src/Regression/Ksl/LinRegr_p.h \
    src/Plotting/Ksl/TextLabelPlot.h \
    src/Plotting/Ksl/TextLabelPlot_p.h

SOURCES += \
    tests/chart.cpp \
    src/Core/Ksl/MemoryPool.cpp \
    src/Plotting/Ksl/CanvasWindow.cpp \
    src/Plotting/Ksl/ChartWindow.cpp \
    src/Plotting/Ksl/Figure.cpp \
    src/Plotting/Ksl/FigureItem.cpp \
    src/Plotting/Ksl/FigureScale.cpp \
    src/Plotting/Ksl/FigureWidget.cpp \
    src/Plotting/Ksl/XYAxis.cpp \
    src/Plotting/Ksl/XYAxisSampler.cpp \
    src/Plotting/Ksl/XYPlot.cpp \
    src/Plotting/Ksl/XYScale.cpp \
    src/Regression/Ksl/LinRegr.cpp \
    src/Plotting/Ksl/TextLabelPlot.cpp

RESOURCES += \
    src/QRC/Icons.qrc
