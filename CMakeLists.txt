cmake_minimum_required(VERSION 2.8.12)

set(APP_NAME whatismyip)
project(${APP_NAME})

find_package(Threads REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -ansi -Wno-deprecated -pthread -std=c++11)
endif()

enable_testing()

add_subdirectory(bin)
add_subdirectory(src)
add_subdirectory(test)
