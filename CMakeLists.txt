cmake_minimum_required(VERSION 3.11...3.17)

# Set the project name and a few useful settings.
project(3d-math
    DESCRIPTION "A simple 3D math library."
    LANGUAGES CXX)

# Set the c++ standard.
set(CMAKE_CXX_STANDARD 11)

# Generate the compilation database for Unix Makefile builds.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# CTest is the CMake test driver program.
include(CTest)

# FetchContent downloads assets during the configure step.
include(FetchContent)

# FetchContent_MakeAvailable was not added until 3.14
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()

# Bring googletest into the project.
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(googletest)

# Make the headers available to the rest of the project.
include_directories(include)

# This will launch the CMakeLists.txt file in the ./src directory.
add_subdirectory(src)

# This will launch the CMakeLists.txt file in the ./tests directory.
add_subdirectory(tests)
