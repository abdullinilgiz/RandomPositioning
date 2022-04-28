cmake_minimum_required(VERSION 3.20)
project(RandomPositioning)

set(CMAKE_CXX_STANDARD 20)

add_executable(RandomPositioning main.cpp randomc.h mersenne.cpp operations.h operations.cpp)
