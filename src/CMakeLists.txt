cmake_minimum_required(VERSION 3.10)
project(Calculator)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# sudo apt-get install qt5-default
find_package(Qt5 COMPONENTS Widgets REQUIRED)

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

target_link_libraries(calc Qt5::Widgets mathlib)