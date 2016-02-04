
TEMPLATE = app
TARGET = Gde_test
CONFIG -= qt
CONFIG += c++11
DEFINES += GDE_DEBUG_BUILD
INCLUDEPATH += ./ ../

HEADERS += \
    Global.h \
    Array1D.h \
    LinReg.h \
    Math.h

SOURCES += \
    main.cpp \
    LinReg.cpp

