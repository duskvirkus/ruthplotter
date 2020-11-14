cmake_minimum_required(VERSION 3.17)
project(locomoteToTest C)

set(CMAKE_C_STANDARD 11)

set ( CMAKE_C_FLAGS "-lm")

add_executable(locomoteToTest main.c)