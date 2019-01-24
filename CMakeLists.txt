cmake_minimum_required(VERSION 3.9)
project(uoft_task)

set(CMAKE_CXX_STANDARD 14)

#set(CMAKE_C_COMPILER "/usr/local/Cellar/llvm/5.0.1/bin/clang")
#set(CMAKE_CXX_COMPILER "/usr/local/Cellar/llvm/5.0.1/bin/clang++")
set(OPENMP_LIBRARIES "/usr/local/Cellar/llvm/5.0.1/lib")
set(OPENMP_INCLUDES "/usr/local/Cellar/llvm/5.0.1/include")

OPTION(USE_OpenMP "Use OpenMP to enamble <omp.h>" ON)

# Find OpenMP
if (APPLE AND USE_OpenMP)
    if (CMAKE_C_COMPILER_ID MATCHES "Clang")
        set(OpenMP_C "${CMAKE_C_COMPILER}")
        set(OpenMP_C_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
        set(OpenMP_C_LIB_NAMES "libomp" "libgomp" "libiomp5")
        set(OpenMP_libomp_LIBRARY ${OpenMP_C_LIB_NAMES})
        set(OpenMP_libgomp_LIBRARY ${OpenMP_C_LIB_NAMES})
        set(OpenMP_libiomp5_LIBRARY ${OpenMP_C_LIB_NAMES})
    endif ()
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(OpenMP_CXX "${CMAKE_CXX_COMPILER}")
        set(OpenMP_CXX_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
        set(OpenMP_CXX_LIB_NAMES "libomp" "libgomp" "libiomp5")
        set(OpenMP_libomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
        set(OpenMP_libgomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
        set(OpenMP_libiomp5_LIBRARY ${OpenMP_CXX_LIB_NAMES})
    endif ()
endif ()

if (USE_OpenMP)
    find_package(OpenMP REQUIRED)
endif (USE_OpenMP)

if (OPENMP_FOUND)
    include_directories("${OPENMP_INCLUDES}")
    link_directories("${OPENMP_LIBRARIES}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    # set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif (OPENMP_FOUND)

## added -fopenmp
#find_package(OpenMP REQUIRED)
#if (OPENMP_FOUND)
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS} -v")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -v")
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS} -v")
#endif ()

add_subdirectory(tests/)

include_directories(.)
include_directories(data)
include_directories(src)
include_directories(src/solver)
include_directories(src/storage)
include_directories(src/utils)
include_directories(tests/)

add_executable(uoft_task src/main.cpp)