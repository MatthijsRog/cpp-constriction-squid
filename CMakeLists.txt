cmake_minimum_required(VERSION 3.13)  # CMake version check

project(cpp-constriction-squid)

set(CMAKE_CXX_STANDARD 20)            # Enable c++14 standard

# Add main.cpp file of the project root directory as a source file
set(SOURCE_FILES src/Main.cpp include/Superconductor.h src/Superconductor.cpp include/Geometry.h src/Geometry.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(MainApplication ${SOURCE_FILES} include/Superconductor.h src/Superconductor.cpp)
add_subdirectory(tests)
