cmake_minimum_required(VERSION 3.16)

project(lab2c)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

add_subdirectory(domino)

add_subdirectory(tests)

add_executable(lab2c main.cpp)

target_link_libraries(lab2c domino)
