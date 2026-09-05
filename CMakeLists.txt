cmake_minimum_required(VERSION 3.20)
project(factorycode)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/wasmtime/crates/c-api
        ${CMAKE_CURRENT_BINARY_DIR}/wasmtime)

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
        ${CMAKE_CURRENT_SOURCE_DIR}/wasmtime
)
target_link_libraries(factorycode_lib PUBLIC wasmtime)

add_executable(factorycode main.cpp)
target_link_libraries(factorycode PRIVATE factorycode_lib)

enable_testing()
add_subdirectory(tests)
