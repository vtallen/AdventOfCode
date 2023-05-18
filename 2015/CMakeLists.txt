cmake_minimum_required(VERSION 3.25)
project(CMakeTemplate)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES
    main.cpp
    AOC2015.h
    day1.cpp
    day2.cpp
    day3.cpp
    day4.cpp
    day5.cpp
)

add_executable(main ${SOURCES})
