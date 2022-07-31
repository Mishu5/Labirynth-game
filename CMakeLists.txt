cmake_minimum_required(VERSION 3.20)
project(Labirynt)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Labirynt
        Labirynt.cpp
        source.cpp
        Source.h)
