cmake_minimum_required(VERSION 4.1)

project("Stack Implementation in C" C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED true)

set(SOURCES src/main.c)

add_executable(main ${SOURCES})