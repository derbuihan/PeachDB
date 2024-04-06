cmake_minimum_required(VERSION 3.14)
project(PeachDB C)
set(CMAKE_C_STANDARD 11)

include_directories(src)
add_executable(PeachDB src/main.c src/parsers/tokenize.c src/parsers/parse.c)
