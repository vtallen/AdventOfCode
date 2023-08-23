project(main)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES
    main.cpp

    ../AOCHelpers/AOCHelpers.h
    ../AOCHelpers/AOCHelpers.cpp
    ../AOCHelpers/md5.h
    ../AOCHelpers/md5.cpp

    AOC2015.h
    day1.cpp
    day2.cpp
    day3.cpp
    day4.cpp
    day5.cpp
    day6.cpp
    day7.cpp
    day8.cpp
    day10.cpp
)

add_executable(main ${SOURCES})
