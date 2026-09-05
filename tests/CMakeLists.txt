include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.7.1
)

FetchContent_MakeAvailable(Catch2)

add_executable(unit_tests
    test_material.cpp
    test_game.cpp
    test_entity.cpp
    test_grid.cpp
    test_logging.cpp
    test_machines.cpp
    test_channel.cpp
)

target_link_libraries(unit_tests PRIVATE
    factorycode_lib
    Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(unit_tests)
