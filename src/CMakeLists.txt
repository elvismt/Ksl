
set(Ksl_HDRS
    Core/Ksl/Global.h
    Core/Ksl/Math.h
    Core/Ksl/Array.h
    Plotting/Ksl/Figure.h
    Plotting/Ksl/FigureScale.h
    Plotting/Ksl/FigureItem.h
    Plotting/Ksl/XYScale.h
    Plotting/Ksl/BasePlot.h
    Plotting/Ksl/Plot.h
    Plotting/Ksl/FigureLegend.h
    Plotting/Ksl/XYAxis.h
    Plotting/Ksl/XYAxisSampler.h
    Plotting/Ksl/FigureLegend.h
    Plotting/Ksl/LinePlot.h
    Plotting/Ksl/TextPlot.h
    Plotting/Ksl/PolyPlot.h
    Plotting/Ksl/CanvasWindow.h
    Plotting/Ksl/FigureWidget.h
    Plotting/Ksl/Chart.h
    Regression/Ksl/LineRegr.h
    Regression/Ksl/MultiLineRegr.h
)

set(Ksl_SRCS
    Core/Ksl/Global.cpp
    Core/Ksl/Csv.cpp
    Plotting/Ksl/Figure.cpp
    Plotting/Ksl/FigureScale.cpp
    Plotting/Ksl/FigureItem.cpp
    Plotting/Ksl/XYScale.cpp
    Plotting/Ksl/BasePlot.cpp
    Plotting/Ksl/Plot.cpp
    Plotting/Ksl/FigureLegend.cpp
    Plotting/Ksl/XYAxis.cpp
    Plotting/Ksl/XYAxisSampler.cpp
    Plotting/Ksl/FigureLegend.cpp
    Plotting/Ksl/LinePlot.cpp
    Plotting/Ksl/TextPlot.cpp
    Plotting/Ksl/PolyPlot.cpp
    Plotting/Ksl/CanvasWindow.cpp
    Plotting/Ksl/FigureWidget.cpp
    Plotting/Ksl/Chart.cpp
    Regression/Ksl/LineRegr.cpp
    Regression/Ksl/MultiLineRegr.cpp
)

qt4_add_resources(Ksl_QRC_SRCS
    QRC/Icons.qrc
)

add_library(Ksl SHARED ${Ksl_SRCS} ${Ksl_QRC_SRCS})
target_link_libraries(Ksl ${QT_LIBRARIES} -lgsl -lgslcblas)
