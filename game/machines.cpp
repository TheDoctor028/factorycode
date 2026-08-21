#include "machines.h"
#include "logging.h"

#include <string>
#include <utility>

namespace factorycode {

    Machine::Machine(Recipe recipe) : recipe(std::move(recipe)) {
    }

    void Machine::tick() {
        Entity::tick();

        if (progress == 0 && can_craft()) {
            input_inventory -= recipe.input;
            inventory += recipe.input;
            debug("[" + entityType() + ": " + recipe.name + "] Started crafting at " +
                  to_string(position) + " with input=" + to_string(recipe.input));
        }

        if (!inventory.empty()) {
            if (progress == recipe.time) {
                progress = 0;
                inventory.clear();
                output_inventory += recipe.output;
                debug("[" + entityType() + ": " + recipe.name + "] Finished crafting at " +
                      to_string(position) + " produced output=" + to_string(recipe.output) +
                      ", output_inventory=" + to_string(output_inventory));
            } else {
                progress++;
                debug("[" + entityType() + ": " + recipe.name + "] Crafting progress: " +
                      std::to_string(progress) + "/" + std::to_string(recipe.time) + " at " +
                      to_string(position));
            }
        }
    }

    MaterialStackList Machine::unload() {
        MaterialStackList output = output_inventory;
        output_inventory.clear();
        if (!output.empty()) {
            debug("[" + entityType() + ": " + recipe.name + "] Unloaded " +
                  to_string(output) + " from position " + to_string(position));
        }
        return output;
    }

    void Machine::load(const MaterialStackList& materials) {
        if (!materials.empty()) {
            input_inventory += materials;
            debug("[" + entityType() + ": " + recipe.name + "] Loaded " +
                  to_string(materials) + " at position " + to_string(position) +
                  ", total input_inventory=" + to_string(input_inventory));
        }
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

        if (!input_inventory.empty()) {
            debug("[" + entityType() + "] Moving input " + to_string(input_inventory) +
                  " to output at position " + to_string(position));
            output_inventory += input_inventory;
            input_inventory.clear();
        }
    }

    Connection::Connection(Machine& in, Machine& out) : input(in), output(out) {}

    void Connection::tick() {
        Entity::tick();
        MaterialStackList transferred = input.unload();
        if (!transferred.empty()) {
            debug("[" + entityType() + "] Transferring " + to_string(transferred) +
                  " from " + to_string(input.get_position()) +
                  " to " + to_string(output.get_position()));
            output.load(transferred);
        }
    }

}
