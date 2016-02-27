TEMPLATE = app
TARGET = Ksl
INCLUDEPATH += ./ ../
CONFIG += c++11
QT += widgets

HEADERS += \
    Array.h \
    Figure.h \
    Global.h \
    Math.h \
    Figure_p.h \
    FigureScale.h \
    FigureScale_p.h \
    Object.h \
    Object_p.h \
    CanvasWindow.h \
    CanvasWindow_p.h \
    FigureItem.h \
    FigureItem_p.h

SOURCES += \
    Figure.cpp \
    FigureScale.cpp \
    CanvasWindow.cpp \
    FigureItem.cpp

RESOURCES += \
    ../../qrc/Icons.qrc
