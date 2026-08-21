#include "machines.h"

#include <utility>

namespace factorycode {

    Machine::Machine(Recipe recipe) : recipe(std::move(recipe)) {
    }

    void Machine::tick() {
        Entity::tick();

        if (progress == 0 && can_craft()) {
            input_inventory -= recipe.input;
            inventory += recipe.input;
        }

        if (!inventory.empty()) {
            if (progress == recipe.time) {
                progress = 0;
                inventory.clear();
                output_inventory += recipe.output;
            } else {
                progress++;
            }
        }
    }

    MaterialStackList Machine::unload() {
        MaterialStackList output = output_inventory;
        output_inventory.clear();
        return output;
    }

    void Machine::load(const MaterialStackList& materials) {
        input_inventory += materials;
    }

    bool Machine::can_craft() {
        return recipe.input <= input_inventory;
    }

    void Machine::process() {
    }

    Producer::Producer(const Recipe& recipe) : Machine(recipe) {
        // input = {};
    }

    Consumer::Consumer(const Recipe& recipe) : Machine(recipe) {
        // output = {};
    }

    Conveyor::Conveyor() : Machine(NoneVoid) {}

    void Conveyor::tick() {
        Entity::tick();

        output_inventory += input_inventory;
        input_inventory.clear();
    }

    Connection::Connection(Machine& in, Machine& out) : input(in), output(out) {}

    void Connection::tick() {
        Entity::tick();
        output.load(input.unload());
    }

}
