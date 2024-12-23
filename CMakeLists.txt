cmake_minimum_required(VERSION 3.29)
project(bfs)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(Parlay REQUIRED)

include_directories(src)

set(PARLAY_NUM_THREADS 4)

add_executable(bench src/bfs.cpp bench/bench.cpp)
add_executable(test src/bfs.cpp test/test.cpp)
