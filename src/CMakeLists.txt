
set(Ksl_HDRS
    Ksl/Global.h
    Ksl/Math.h
    Ksl/Array.h
    Ksl/Figure.h
    Ksl/FigureScale.h
    Ksl/FigureItem.h
    Ksl/XYScale.h
    Ksl/XYPlot.h
    Ksl/XYAxis.h
    Ksl/XYAxisSampler.h
    Ksl/CanvasWindow.h
    Ksl/FigureWidget.h
    Ksl/ChartWindow.h
    Ksl/Regression/Linear.h
)

set(Ksl_SRCS
    Ksl/Figure.cpp
    Ksl/FigureScale.cpp
    Ksl/FigureItem.cpp
    Ksl/XYScale.cpp
    Ksl/XYPlot.cpp
    Ksl/XYAxis.cpp
    Ksl/XYAxisSampler.cpp
    Ksl/CanvasWindow.cpp
    Ksl/FigureWidget.cpp
    Ksl/ChartWindow.cpp
    Ksl/Regression/Linear.cpp
)

QT4_ADD_RESOURCES(
    ICONS_QRC
    qrc/Icons.qrc
)

add_library(Ksl SHARED ${Ksl_SRCS} ${ICONS_QRC})
target_link_libraries(Ksl ${QT_LIBRARIES})
