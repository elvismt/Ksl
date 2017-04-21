TEMPLATE = app
TARGET = Ksl
QT += widgets
INCLUDEPATH += src/include

HEADERS += \
    src/include/ksl/plot/Object.h \
    src/include/ksl/plot/Object_h.h \
    src/include/ksl/plot/FigureView.h \
    src/include/ksl/plot/FigureView_p.h \
    src/include/ksl/plot/Figure.h \
    src/include/ksl/plot/Figure_p.h \
    src/include/ksl/plot/FigureScale.h \
    src/include/ksl/plot/FigureScale_p.h

SOURCES += \
    src/ksl/plot/test.cpp \
    src/ksl/plot/FigureView.cpp \
    src/ksl/plot/Figure.cpp \
    src/ksl/plot/FigureScale.cpp
