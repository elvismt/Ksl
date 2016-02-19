
add_executable(sine sine.cpp)
target_link_libraries(sine Ksl)

add_executable(scatter scatter.cpp)
target_link_libraries(scatter Ksl)

add_executable(devtest devtest.cpp)
target_link_libraries(devtest Ksl)
