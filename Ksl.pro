
TEMPLATE = app
TARGET = Ksl_test

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
    CONFIG += c++11
}
lessThan(QT_MAJOR_VERSION, 5) {
    QMAKE_CXXFLAGS += -std=c++11
}

LIBS += -lgsl -lgslcblas


# Input
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
    src/Core/Ksl/Functions.h \
    src/Core/Ksl/Csv.h \
    src/Core/Ksl/Csv_p.h \
    src/Plotting/Ksl/CanvasWindow.h \
    src/Plotting/Ksl/CanvasWindow_p.h \
    src/Plotting/Ksl/Chart.h \
    src/Plotting/Ksl/Chart_p.h \
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
    src/Plotting/Ksl/XYScale.h \
    src/Plotting/Ksl/XYScale_p.h \
    src/Plotting/Ksl/TextPlot.h \
    src/Plotting/Ksl/TextPlot_p.h \
    src/Plotting/Ksl/LinePlot.h \
    src/Plotting/Ksl/LinePlot_p.h \
    src/Plotting/Ksl/PolyPlot.h \
    src/Plotting/Ksl/PolyPlot_p.h \
    src/Regression/Ksl/LineRegr.h \
    src/Regression/Ksl/LineRegr_p.h \
    src/Regression/Ksl/MultiLineRegr.h \
    src/Regression/Ksl/MultiLineRegr_p.h \
    src/Plotting/Ksl/BasePlot.h \
    src/Plotting/Ksl/BasePlot_p.h \
    src/Plotting/Ksl/Plot.h \
    src/Plotting/Ksl/Plot_p.h \
    src/Plotting/Ksl/FigureLegend.h \
    src/Plotting/Ksl/FigureLegend_p.h \
    src/Plotting/Ksl/FeaturePlot.h \
    src/Plotting/Ksl/FeaturePlot_p.h

SOURCES += \
    tests/devtest.cpp \
    src/Core/Ksl/MemoryPool.cpp \
    src/Core/Ksl/Csv.cpp \
    src/Plotting/Ksl/CanvasWindow.cpp \
    src/Plotting/Ksl/Chart.cpp \
    src/Plotting/Ksl/Figure.cpp \
    src/Plotting/Ksl/FigureItem.cpp \
    src/Plotting/Ksl/FigureScale.cpp \
    src/Plotting/Ksl/FigureWidget.cpp \
    src/Plotting/Ksl/XYAxis.cpp \
    src/Plotting/Ksl/XYAxisSampler.cpp \
    src/Plotting/Ksl/XYScale.cpp \
    src/Plotting/Ksl/TextPlot.cpp \
    src/Plotting/Ksl/LinePlot.cpp \
    src/Plotting/Ksl/PolyPlot.cpp \
    src/Regression/Ksl/LineRegr.cpp \
    src/Regression/Ksl/MultiLineRegr.cpp \
    src/Plotting/Ksl/BasePlot.cpp \
    src/Plotting/Ksl/Plot.cpp \
    src/Plotting/Ksl/FigureLegend.cpp \
    src/Plotting/Ksl/FeaturePlot.cpp

RESOURCES += \
    src/QRC/Icons.qrc
