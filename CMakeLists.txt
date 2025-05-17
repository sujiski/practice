cmake_minimum_required(VERSION 3.14)
project(acc_simulation)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(acc_simulation ${SOURCES} main.cpp)
