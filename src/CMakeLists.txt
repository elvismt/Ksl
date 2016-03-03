
set(Ksl_HDRS
    Core/Ksl/Global.h
    Core/Ksl/Math.h
    Core/Ksl/Array.h
    Plotting/Ksl/Figure.h
    Plotting/Ksl/FigureScale.h
    Plotting/Ksl/FigureItem.h
    Plotting/Ksl/XYScale.h
    Plotting/Ksl/XYPlot.h
    Plotting/Ksl/XYAxis.h
    Plotting/Ksl/XYAxisSampler.h
    Plotting/Ksl/CanvasWindow.h
    Plotting/Ksl/FigureWidget.h
    Plotting/Ksl/ChartWindow.h
    Regression/Ksl/LinRegr.h
)

set(Ksl_SRCS
    Plotting/Ksl/Figure.cpp
    Plotting/Ksl/FigureScale.cpp
    Plotting/Ksl/FigureItem.cpp
    Plotting/Ksl/XYScale.cpp
    Plotting/Ksl/XYPlot.cpp
    Plotting/Ksl/XYAxis.cpp
    Plotting/Ksl/XYAxisSampler.cpp
    Plotting/Ksl/CanvasWindow.cpp
    Plotting/Ksl/FigureWidget.cpp
    Plotting/Ksl/ChartWindow.cpp
    Regression/Ksl/LinRegr.cpp
)

qt4_add_resources(Ksl_QRC_SRCS
    QRC/Icons.qrc
)

add_library(Ksl SHARED ${Ksl_SRCS} ${Ksl_QRC_SRCS})
target_link_libraries(Ksl ${QT_LIBRARIES})
