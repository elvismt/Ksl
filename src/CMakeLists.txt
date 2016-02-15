
set(Ksl_HDRS
    Ksl/array1d.h
    Ksl/chart.h
    Ksl/chartitem.h
    Ksl/chartlinscale.h
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
    Ksl/chartlinscale.cpp
    Ksl/chartscale.cpp
    Ksl/chartview.cpp
    Ksl/simpleplot.cpp
)

add_library(Ksl ${Ksl_SRCS} ${Ksl_HDRS})
