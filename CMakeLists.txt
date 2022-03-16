cmake_minimum_required(VERSION 3.7)

project(purestomp VERSION 1.1.0)

add_subdirectory(stomptalk)

add_executable(purestomp main.c)
set_property(TARGET purestomp PROPERTY C_STANDARD 11)

target_link_libraries(purestomp PRIVATE stomptalk)
