# Set Name of project and language
project(Ex4 LANGUAGES CXX)

# Set cmake version
cmake_minimum_required(VERSION 3.0)

# set build type to Debug/Release
set(CMAKE_BUILD_TYPE "Debug")

# Create executable using the specified src
add_executable(${PROJECT_NAME} ex4.cpp)

# Define required c++ standard to C++17
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

# Set compile options, enable warnings
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>: -Wall>
    $<$<CXX_COMPILER_ID:MSVC>: /Wall>
)
