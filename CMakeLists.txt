project(Ksl CXX)
cmake_minimum_required(VERSION 2.8)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(UNIX)

set(CMAKE_AUTOMOC ON)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

include_directories(
    src/Core
    src/Plotting
    src/Regression
)

subdirs(
    src
    tests
)
