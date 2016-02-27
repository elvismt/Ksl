
set(Ksl_HDRS
    Ksl/Global.h
    Ksl/Math.h
    Ksl/Array.h
    Ksl/Figure.h
    Ksl/FigureScale.h
    Ksl/FigureItem.h
    Ksl/CanvasWindow.h
)

set(Ksl_SRCS
    Ksl/Figure.cpp
    Ksl/FigureScale.cpp
    Ksl/FigureItem.cpp
    Ksl/CanvasWindow.cpp
)

QT5_ADD_RESOURCES(
    ICONS_QRC
    qrc/Icons.qrc
)

add_library(Ksl SHARED ${Ksl_SRCS} ${ICONS_QRC})
target_link_libraries(Ksl Qt5::Widgets)

