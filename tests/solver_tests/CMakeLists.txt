# tests - cmake file

cmake_minimum_required(VERSION 3.9)
project(gtests_uoft_solvers)

include_directories(../lib/googletest-release-1.8.1/googletest/include)
include_directories(../lib/googletest-release-1.8.1/googlemock/include)

if (CYGWIN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
endif (CYGWIN)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)


add_executable(runTestSolver ../main.cpp ./solver_simple_test.cpp sparse_solver_test.cpp sparse_parallel_solver_test.cpp)
target_link_libraries(runTestSolver gtest gtest_main)