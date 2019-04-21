cmake_minimum_required(VERSION 3.10)
project(linuxsp)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(process)
add_subdirectory(time)
add_subdirectory(memory)
add_subdirectory(ipc)
add_subdirectory(thread)
add_subdirectory(io)
add_subdirectory(bufio)
add_subdirectory(pipe)