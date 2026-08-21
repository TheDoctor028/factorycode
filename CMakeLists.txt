add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/wasmtime/crates/c-api
        ${CMAKE_CURRENT_BINARY_DIR}/wasmtime)

cmake_minimum_required(VERSION 4.3)
project(factorycode)

set(CMAKE_CXX_STANDARD 26)

add_executable(factorycode main.cpp lib/channel/channel.hpp lib/channel/channel.cpp
        game/Game.cpp
        game/Game.h
        game/materials.h
        game/materials.cpp
        game/materials.cpp
        game/Recipe.h
        game/grid.h
)

target_include_directories(factorycode PUBLIC wasmtime)
target_link_libraries(factorycode PUBLIC wasmtime)
