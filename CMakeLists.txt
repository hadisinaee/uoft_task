cmake_minimum_required(VERSION 3.9)
project(uoft_task)

set(CMAKE_CXX_STANDARD 14)

# added -fopenmp
find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS} ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} ")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS} ")
endif ()

add_subdirectory(tests/)
add_subdirectory(tests/solver_tests)


include_directories(.)
include_directories(include)
include_directories(include/solver)
include_directories(include/storage)
include_directories(include/utils)


add_executable(uoft_task
        src/main.cpp

        src/solver/sparse_solver.cpp
        src/solver/simple_solver.cpp
        src/solver/sparse_parallel_solver.cpp

        src/storage/mtx_vector.cpp
        src/storage/mtx_matrix.cpp

        src/utils/dfs.cpp)