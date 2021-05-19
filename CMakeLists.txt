cmake_minimum_required(VERSION 3.7)

project(purestomp VERSION 1.0.1)

add_subdirectory(stomptalk)

add_executable(purestomp main.c)
target_link_libraries(purestomp PRIVATE stomptalk)
