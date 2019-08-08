cmake_minimum_required(VERSION 3.0)
project(PrintDebugPerf C)

set(CMAKE_C_STANDARD 99)

add_executable(PrintDebugPerf main.c StudentCode.c TestCode.c TestCode.h)

target_link_libraries(PrintDebugPerf cmocka)
