cmake_minimum_required(VERSION 3.3)
project(Project_3_Related_Files)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    p3.cpp
    simulation.cpp
    simulation.h
    world_type.h)

add_executable(Project_3_Related_Files ${SOURCE_FILES})