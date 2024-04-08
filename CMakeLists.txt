cmake_minimum_required(VERSION 3.14)
project(PeachDB C)
set(CMAKE_C_STANDARD 11)

add_subdirectory(src/parser)

include_directories(${CMAKE_CURRENT_BINARY_DIR}/src/parser src)
add_executable(PeachDB src/main.c src/executor/executor.c src/storage/storage.c)
target_link_libraries(PeachDB parser)
