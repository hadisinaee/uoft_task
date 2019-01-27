# tests - cmake file

cmake_minimum_required(VERSION 3.9)
project(gtests_uoft_solvers)

include_directories(.)
include_directories(../../include/storage)
include_directories(../../include/solver)
include_directories(../../include/utils)

include_directories(../lib/googletest-release-1.8.1/googletest/include)
include_directories(../lib/googletest-release-1.8.1/googlemock/include)

if (CYGWIN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
endif (CYGWIN)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)


add_executable(testSolver
        ../../src/utils/dfs.cpp

        ../../src/solver/simple_solver.cpp
        ../../src/solver/sparse_solver.cpp
        ../../src/solver/sparse_parallel_solver.cpp

        ../../src/storage/mtx_vector.cpp
        ../../src/storage/mtx_matrix.cpp

        main_test.cpp

        solver_simple_test.cpp
        sparse_solver_test.cpp
        sparse_parallel_solver_test.cpp

        )

target_link_libraries(testSolver gtest gtest_main)