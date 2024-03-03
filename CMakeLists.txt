cmake_minimum_required(VERSION 3.27)
project(university)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(.)

add_executable(university
        main.cpp
        backpack_algo.h
        pareto.h
        SetCoveProblem.h
        interface.h
)
