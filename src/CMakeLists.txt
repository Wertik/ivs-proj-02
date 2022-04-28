cmake_minimum_required(VERSION 3.10)
project(Calculator)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# sudo apt-get install qt5-default
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# add gtest
#add_subdirectory(build/libs/googletest)

# libraries
add_library(
    mathlib
    mathlib/mathlib.h
    mathlib/mathlib.cpp
)

target_include_directories(mathlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# calc executable
add_executable(calc
    mainwindow.ui
    mainwindow.cpp
    mainwindow.h
    main.cpp
)

# test executable
#add_executable(mathtest ${CMAKE_CURRENT_SOURCE_DIR}/tests/tests.cpp)

# profiling executable
#add_executable(stddev ${CMAKE_CURRENT_SOURCE_DIR}/profiling/stddev.cpp)

#target_link_libraries(stddev mathlib)
#target_link_libraries(mathtest PRIVATE mathlib gtest gtest_main)
target_link_libraries(calc Qt5::Widgets mathlib)