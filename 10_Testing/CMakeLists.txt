cmake_minimum_required(VERSION 3.22)
project(Test)
enable_testing()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g -fprofile-arcs -ftest-coverage")


add_library(Buf SHARED buf.c)

add_subdirectory("tests")

include(CTest)