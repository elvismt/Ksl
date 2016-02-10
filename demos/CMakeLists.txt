
add_executable(scatter scatter.cpp)
target_link_libraries(scatter Ksl ${QT_LIBRARIES})

add_executable(trigonometry trigonometry.cpp)
target_link_libraries(trigonometry Ksl ${QT_LIBRARIES})
