
set(QSL_HDRS
   QSL/Global.h
   QSL/Object.h
   QSL/ObjectPrivate.h
   QSL/Array1D.h
   QSL/Figure.h
   QSL/FigureItem.h
   QSL/FigureScale.h
   QSL/FigureWidget.h
   QSL/LinearScale.h
   QSL/SimpleSeries.h
)

set(QSL_SRCS
   QSL/Figure.cpp
   QSL/FigureItem.cpp
   QSL/FigureScale.cpp
   QSL/FigureWidget.cpp
   QSL/LinearScale.cpp
   QSL/SimpleSeries.cpp
)

add_library(qsl SHARED ${QSL_SRCS})
target_link_libraries(qsl Qt5::Widgets)

install(TARGETS qsl DESTINATION /usr/lib)
install(FILES ${QSL_HDRS} DESTINATION /usr/include/QSL)

