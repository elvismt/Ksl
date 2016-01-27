include_directories("${CMAKE_SOURCE_DIR}/src")

add_executable(minimal minimal.cpp)
target_link_libraries(minimal qsl)

