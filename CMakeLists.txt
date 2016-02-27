project(Ksl CXX)
cmake_minimum_required(VERSION 2.8)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(UNIX)

set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets)
include_directories(src)

subdirs(
    src
    tests
)

