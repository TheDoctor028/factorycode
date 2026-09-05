#include <catch2/catch_test_macros.hpp>
#include "game/game.h"
#include "game/recipe.h"

using namespace factorycode;

TEST_CASE("Full factory simulation workflow from main", "[integration][game]") {
    Game game;

    auto coalMine = Producer(recipes_v2.at(Operation::Mine).at(Material::Coal));
    auto ironMine = Producer(recipes_v2.at(Operation::Mine).at(Material::IronOre));
    auto conveyor = Conveyor();
    auto smelter = Machine(recipes_v2.at(Operation::Smelt).at(Material::Iron));

    SECTION("Place machines, connect conveyor pipeline, and run ticks") {
        game.place(coalMine, {0, 0});
        game.place(ironMine, {1, 0});
        game.place(conveyor, {0, 1});
        game.place(smelter, {1, 1});

        REQUIRE(game.connectMachines(coalMine, conveyor));
        REQUIRE(game.connectMachines(ironMine, smelter));
        REQUIRE(game.connectMachines(conveyor, smelter));

        // Run 22 ticks of the game loop
        for (int i = 0; i < 22; ++i) {
            REQUIRE_NOTHROW(game.tick());
        }
    }
}
