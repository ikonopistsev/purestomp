cmake_minimum_required(VERSION 3.7)

project(purestomp VERSION 2.0.1 LANGUAGES C)

# Without optimization the stomptalk parser runs its states from a slow loop.
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_subdirectory(stomptalk)

add_executable(purestomp main.c)
set_property(TARGET purestomp PROPERTY C_STANDARD 11)

# we need to link against stomptalk and the C++ standard library
if (MSVC)
    target_link_libraries(purestomp PRIVATE stomptalk)
else()
    target_link_libraries(purestomp PRIVATE stomptalk stdc++)
endif()
