cmake_minimum_required(VERSION 3.22)
project(simple_directx_game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)

# set variable for files names

set(Debug_Window_Class window_class_debug.h window_class_debug.cpp)

add_executable(simple_directx_game main.cpp ${Debug_Window_Class}
        p_windows_simple.h)
