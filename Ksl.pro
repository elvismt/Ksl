TEMPLATE = app
TARGET = Ksl
QT += widgets
INCLUDEPATH += src/include

HEADERS += \
    src/include/ksl/Object.h \
    src/include/ksl/Object_h.h \
    src/include/ksl/plot/FigureView.h \
    src/include/ksl/plot/FigureView_p.h \
    src/include/ksl/plot/Figure.h \
    src/include/ksl/plot/Figure_p.h \
    src/include/ksl/plot/FigureScale.h \
    src/include/ksl/plot/FigureScale_p.h \
    src/include/ksl/plot/FigureItem.h \
    src/include/ksl/plot/FigureItem_p.h \
    src/include/ksl/plot/LinearScale.h \
    src/include/ksl/plot/LinearScale_p.h \
    src/include/ksl/plot/Series.h \
    src/include/ksl/plot/Series_p.h \
    src/include/ksl/plot/Util.h \
    src/include/ksl/random/Normal.h \
    src/include/ksl/random/Normal_p.h \
    src/include/ksl/random/Distribution.h \
    src/include/ksl/random/Distribution_p.h \
    src/include/ksl/plot/Axis.h \
    src/include/ksl/plot/Axis_p.h \
    src/include/ksl/plot/Plot.h \
    src/include/ksl/plot/Plot_p.h \
    src/include/ksl/plot/Chart.h \
    src/include/ksl/plot/Chart_p.h

SOURCES += \
    test.cpp \
    src/ksl/plot/FigureView.cpp \
    src/ksl/plot/Figure.cpp \
    src/ksl/plot/FigureScale.cpp \
    src/ksl/plot/FigureItem.cpp \
    src/ksl/plot/LinearScale.cpp \
    src/ksl/plot/Series.cpp \
    src/ksl/plot/Util.cpp \
    src/ksl/random/Normal.cpp \
    src/ksl/plot/Axis.cpp \
    src/ksl/plot/Plot.cpp \
    src/ksl/plot/Chart.cpp
