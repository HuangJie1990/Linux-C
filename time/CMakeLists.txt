cmake_minimum_required(VERSION 3.13)
project(linuxsp)

set(CMAKE_CXX_STANDARD 14)


add_library(TimeUtils utils.c utils.h)
add_executable(clocksource clocksource.c)
add_executable(getCurrentTime getCurrentTime.c utils.c)
add_executable(timestr timestr.c)
add_executable(sleep sleep.c)
add_executable(posix_timer posix_timer.c utils.c utils.h)
target_link_libraries(posix_timer pthread rt)
add_executable(alarm_timer alarm_timer.cpp)
add_executable(system_timer system_timer.cpp)