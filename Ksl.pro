
TEMPLATE = app
TARGET = Ksl
INCLUDEPATH += ./ src/
CONFIG += c++11
QT += widgets


# Input
HEADERS += \
    src/Ksl/Array.h \
    src/Ksl/Chart.h \
    src/Ksl/Chart_p.h \
    src/Ksl/ChartItem.h \
    src/Ksl/ChartItem_p.h \
    src/Ksl/ChartLinscale.h \
    src/Ksl/ChartLinscale_p.h \
    src/Ksl/ChartScale.h \
    src/Ksl/ChartScale_p.h \
    src/Ksl/ChartView.h \
    src/Ksl/ChartView_p.h \
    src/Ksl/Global.h \
    src/Ksl/Object.h \
    src/Ksl/Object_p.h \
    src/Ksl/SeriesPlot.h \
    src/Ksl/SeriesPlot_p.h \
    src/Ksl/ChartAxis.h \
    src/Ksl/ChartAxis_p.h \
    src/Ksl/ChartLabel.h \
    src/Ksl/ChartLabel_p.h \
    src/Ksl/Math.h \
    src/Ksl/ChartAxisSampler.h \
    src/Ksl/ChartAxisSampler_p.h \
    src/Ksl/MemoryPool.h \
    src/Ksl/MemoryPool_p.h


SOURCES += \
    demos/sinusoidal.cpp \
    src/Ksl/Chart.cpp \
    src/Ksl/ChartItem.cpp \
    src/Ksl/ChartLinscale.cpp \
    src/Ksl/ChartScale.cpp \
    src/Ksl/ChartView.cpp \
    src/Ksl/SeriesPlot.cpp \
    src/Ksl/ChartAxis.cpp \
    src/Ksl/ChartLabel.cpp \
    src/Ksl/Math.cpp \
    src/Ksl/ChartAxisSampler.cpp \
    src/Ksl/MemoryPool.cpp
