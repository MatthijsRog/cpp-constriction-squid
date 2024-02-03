# 'Google_test' is the subproject name
project(Tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(../googletest/ ../googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp test2.cpp' are source files with tests
#add_executable(Run_tests testabstractfield.cpp ../include/Superconductor.h ../src/Superconductor.cpp testsuperconductor.cpp)
add_executable(Run_tests testabstractfield.cpp ../src/Geometry.cpp testgeometry.cpp ../src/Superconductor.cpp testsuperconductor.cpp)
target_link_libraries(Run_tests gtest gtest_main)