
set(Ksl_HDRS
    Ksl/arrayview.h
    Ksl/chart.h
    Ksl/chartitem.h
    Ksl/chartlinearscale.h
    Ksl/chartscale.h
    Ksl/chartview.h
    Ksl/global.h
    Ksl/object.h
    Ksl/object_p.h
    Ksl/simpleplot.h
)

set(Ksl_SRCS
    Ksl/chart.cpp
    Ksl/chartitem.cpp
    Ksl/chartlinearscale.cpp
    Ksl/chartscale.cpp
    Ksl/chartview.cpp
    Ksl/simpleplot.cpp
)

add_library(Ksl ${Ksl_SRCS})
