cmake_minimum_required(VERSION 3.10)
project(linuxsp)

set(CMAKE_CXX_STANDARD 14)

add_executable(io_open open.c)
add_executable(dup dup.c)
add_executable(lseek lseek.c)
add_executable(mmap mmap.c)