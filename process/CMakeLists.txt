cmake_minimum_required(VERSION 3.10)
project(linuxsp)

set(CMAKE_CXX_STANDARD 14)

add_executable(fork fork.c)
add_executable(loop_fork loop_fork.c)
add_executable(execl execl.c)
add_executable(orphen orphen.c)
add_executable(zombie zombie.c)
add_executable(wait wait.c)