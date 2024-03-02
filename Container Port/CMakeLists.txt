cmake_minimum_required(VERSION 3.16)

project(lab3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")


add_subdirectory(terminal)

add_subdirectory(tests)

add_executable(lab3 main.cpp dialog/dialog.h dialog/dialog.cpp)

target_link_libraries(lab3 pthread)
target_link_libraries(lab3 terminal)


