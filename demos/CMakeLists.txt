
add_executable(sinusoidal sinusoidal.cpp)
target_link_libraries(sinusoidal Ksl)

add_executable(scatter scatter.cpp)
target_link_libraries(scatter Ksl)
