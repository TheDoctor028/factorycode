cmake_minimum_required(VERSION 3.20)
project(factorycode)

set(CMAKE_CXX_STANDARD 26)

include(FetchContent)

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/wasmtime-target")
set(ENV{CARGO_TARGET_DIR} "${CMAKE_CURRENT_BINARY_DIR}/wasmtime-target")

FetchContent_Declare(
    wasmtime
    GIT_REPOSITORY https://github.com/bytecodealliance/wasmtime.git
    GIT_TAG        v47.0.1
    GIT_SHALLOW    TRUE
    GIT_SUBMODULES ""
    SOURCE_SUBDIR  crates/c-api
)
FetchContent_MakeAvailable(wasmtime)

set(GAME_SOURCES
        lib/channel/channel.hpp
        lib/channel/channel.cpp
        game/game.cpp
        game/game.h
        game/material.h
        game/material.cpp
        game/recipe.h
        game/grid.h
        game/grid.cpp
        game/entity.cpp
        game/entity.h
        game/machines.cpp
        game/machines.h
        game/logging.cpp
        game/logging.h
)

add_library(factorycode_lib STATIC ${GAME_SOURCES})
target_include_directories(factorycode_lib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(factorycode_lib PUBLIC wasmtime)

add_executable(factorycode main.cpp)
target_link_libraries(factorycode PRIVATE factorycode_lib)

enable_testing()
add_subdirectory(tests)
