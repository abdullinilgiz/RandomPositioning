cmake_minimum_required(VERSION 3.20)
project(RandomPositioning)

set(CMAKE_CXX_STANDARD 20)

add_executable(RandomPositioning main.cpp mersenne.cpp operations.cpp mylibr.cpp)
