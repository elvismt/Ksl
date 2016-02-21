
set(Ksl_HDRS
    Ksl/Array.h
    Ksl/Chart.h
    Ksl/ChartItem.h
    Ksl/ChartLinscale.h
    Ksl/ChartScale.h
    Ksl/ChartView.h
    Ksl/Global.h
    Ksl/Object.h
    Ksl/Object_p.h
    Ksl/SeriesPlot.h
    Ksl/ChartAxis.h
    Ksl/ChartAxisSampler.h
)

set(Ksl_SRCS
    Ksl/Math.cpp
    Ksl/Chart.cpp
    Ksl/ChartItem.cpp
    Ksl/ChartLinscale.cpp
    Ksl/ChartScale.cpp
    Ksl/ChartView.cpp
    Ksl/SeriesPlot.cpp
    Ksl/ChartAxis.cpp
    Ksl/ChartAxisSampler.cpp
)

add_library(Ksl SHARED ${Ksl_SRCS})
target_link_libraries(Ksl Qt5::Widgets)

install(FILES ${Ksl_HDRS} DESTINATION /usr/include/Ksl)
install(TARGETS Ksl DESTINATION /usr/lib)

