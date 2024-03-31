cmake_minimum_required(VERSION 3.14)
project(PeachDB C)

set(CMAKE_C_STANDARD 11)

add_executable(PeachDB main.c tokenize.c)
