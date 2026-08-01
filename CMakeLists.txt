add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/wasmtime/crates/c-api
        ${CMAKE_CURRENT_BINARY_DIR}/wasmtime)

cmake_minimum_required(VERSION 4.3)
project(factorycode)

set(CMAKE_CXX_STANDARD 26)

add_executable(factorycode main.cpp lib/channel/channel.hpp lib/channel/channel.cpp
        game/game.cpp
        game/game.h)

target_include_directories(factorycode PUBLIC wasmtime)
target_link_libraries(factorycode PUBLIC wasmtime)
