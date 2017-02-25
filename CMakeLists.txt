cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OSX_ARCHITECTURES x86_64)

add_subdirectory(external)

option(NGEN_BUILD_TESTS "Build unit tests." ON)

project(ngen_state_system)

include_directories(include)
include_directories(SYSTEM external/ngen/include)

set(SOURCE_FILES
        source/game_state.cpp source/state_tree.cpp)

set(INCLUDE_FILES
        include/game_state.h include/state_tree.h)

add_library(ngen_state_system ${SOURCE_FILES} ${INCLUDE_FILES})

if (NGEN_BUILD_TESTS)
    add_subdirectory(test)
endif()
