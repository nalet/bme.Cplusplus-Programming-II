cmake_minimum_required(VERSION 3.0)

# Set name, version and language of project
project(PCP VERSION 1.0.0 LANGUAGES CXX)

# Declare dependencies
find_package(Threads REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core SerialPort Network Widgets)

# Qt Flags
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
# Instruct CMake to get the resources
set(CMAKE_AUTORCC ON)

# Add target with sources
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/ui/widget.cpp
    src/ui/widget.h
    src/ui/widget.ui
    src/app/common/control.cpp
    src/app/common/control.h
    src/app/common/icontrol.h
    src/app/common/dataBuffer.cpp
    src/app/common/dataBuffer.h
    src/app/common/dataBufferPool.cpp
    src/app/common/dataBufferPool.h
    src/app/acquisition/VCamera.cpp
    src/app/acquisition/VCamera.h
    src/app/acquisition/ivcamera.h
    src/app/visualisation/videoVisualizer.cpp
    src/app/visualisation/videoVisualizer.h
    src/app/visualisation/rOg_image.cpp
    src/app/visualisation/rOg_image.h
    resources/res.qrc   # Resource file
    )

# Set includes
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app/common
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app/acquisition
    ${CMAKE_CURRENT_SOURCE_DIR}/src/app/visualisation
    )

# Link libs
if(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Core PRIVATE Threads::Threads)
else(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Core)
endif(UNIX)

# Set compile options, enable warnings
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall>
    $<$<CXX_COMPILER_ID:MSVC>: /W3>
    )


