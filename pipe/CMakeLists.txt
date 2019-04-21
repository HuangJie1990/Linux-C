cmake_minimum_required(VERSION 3.10)
project(linuxsp)

set(CMAKE_CXX_STANDARD 14)
add_executable(ps_grep ps_grep.c)
add_executable(ps_grep_bro ps_grep_bro.c)
add_executable(fpathconf fpathconf.c)