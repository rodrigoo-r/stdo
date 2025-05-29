include(FetchContent)

FetchContent_Declare(
        stdbool
        GIT_REPOSITORY https://github.com/rodrigoo-r/std_bool
        GIT_TAG        master
)


FetchContent_MakeAvailable(stdbool)
cmake_minimum_required(VERSION 3.30)
project(stdo C)

set(CMAKE_C_STANDARD 11)

add_library(stdo STATIC stdo.c stdo.h)
target_include_directories(stdo PRIVATE ${CMAKE_BINARY_DIR}/_deps/stdbool-src)
target_link_libraries(stdo PRIVATE stdbool)