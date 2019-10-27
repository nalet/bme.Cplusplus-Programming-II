cmake_minimum_required(VERSION 3.5)

project(Ex3 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Quick PrintSupport REQUIRED)

add_executable(Ex3
  main.cpp
  ui/mainwindow.cpp
  ui/mainwindow.h
  ui/mainwindow.ui
  ui/qcustomplot/qcustomplot.cpp
  ui/qcustomplot/qcustomplot.h
)

target_link_libraries(Ex3 PRIVATE Qt5::Widgets Qt5::Quick Qt5::PrintSupport)

configure_file(ekg.txt ekg.txt COPYONLY)
