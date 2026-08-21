#include "game/Game.h"
#include "game/recipe.h"


int main() {
    using namespace factorycode;
    auto game = Game();

    auto coalMine = Machine(recipes_v2.at(Operation::Mine).at(Material::Coal));
    auto ironMine = Machine(recipes_v2.at(Operation::Mine).at(Material::IronOre));

    auto conveyor = Conveyor();

    auto smelter = Machine(recipes_v2.at(Operation::Smelt).at(Material::Iron));

    game.place(coalMine, {0, 0});
    game.place(ironMine, {1, 0});

    game.place(conveyor, {0, 1});

    game.place(smelter, {1, 1});

    game.connectMachines(coalMine, conveyor);
    game.connectMachines(ironMine, smelter);
    game.connectMachines(conveyor, smelter);

    game.tick();
    game.tick();
    game.tick();
    game.tick();
    return 0;
}
