cmake_minimum_required(VERSION 3.10)

project(purestomp VERSION 1.0.0)

add_subdirectory(stomptalk)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} stomptalk/include)

add_executable(purestomp main.c)
target_link_libraries(purestomp PRIVATE stomptalk)
