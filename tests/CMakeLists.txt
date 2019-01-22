cmake_minimum_required(VERSION 3.13)
project(gtests_uoft)

set(CMAKE_CXX_STANDARD 14)

include_directories(lib/googletest-release-1.8.1/googletest/include)
include_directories(lib/googletest-release-1.8.1/googlemock/include)



if (CYGWIN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x")
endif(CYGWIN)

if (APPLE)
    add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
    add_definitions(-D__GLIBCXX__)
endif (APPLE)


add_executable(runTests main.cpp dfs_test.cpp mtx_matrix_test.cpp mtx_vector_test.cpp)
target_link_libraries(runTests gtest gtest_main)