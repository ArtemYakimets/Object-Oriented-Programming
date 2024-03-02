find_package(Catch2 REQUIRED)

add_executable(kdtree_testing test.cpp)

#Include(FetchContent)
#FetchContent_Declare(
#        Catch2
#        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
#        GIT_TAG        v3.0.1 # or a later release
#)
#FetchContent_MakeAvailable(Catch2)

target_link_libraries(kdtree_testing pthread)

target_link_libraries(kdtree_testing terminal Catch2::Catch2WithMain)