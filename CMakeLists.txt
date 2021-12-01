cmake_minimum_required(VERSION 3.17)
project(AOC2021)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(${PROJECT_NAME}_lib
        src/daily_task_01.cpp
        )

add_executable(${PROJECT_NAME}_main
        main.cpp
        )

target_link_libraries(${PROJECT_NAME}_main ${PROJECT_NAME}_lib)
