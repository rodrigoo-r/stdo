cmake_minimum_required(VERSION 3.30)
project(stdo C)

set(CMAKE_C_STANDARD 11)

add_library(stdo STATIC stdo.c stdo.h)
