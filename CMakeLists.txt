cmake_minimum_required(VERSION 3.14)
project(PeachDB C)
set(CMAKE_C_STANDARD 11)

add_subdirectory(src/parsers)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/src/parsers src)
add_executable(PeachDB src/main.c)
target_link_libraries(PeachDB parser)
