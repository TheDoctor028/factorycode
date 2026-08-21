#pragma once

#include <set>

#include "entity.h"
#include "Material.h"
#include "recipe.h"

namespace factorycode {

    class Machine: public Entity {
    public:
        explicit Machine(Recipe recipe): recipe(std::move(recipe)) {
        }
        const Recipe recipe;

        void tick() override {
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

        MaterialStackList unload() {
            MaterialStackList output = output_inventory;
            output_inventory.clear();
            return output;
        }

        void load(const MaterialStackList& materials) {
            input_inventory += materials;
        }
    protected:
        MaterialStackList input_inventory;
        MaterialStackList inventory;
        MaterialStackList output_inventory;

        uint progress = 0;

        bool can_craft() {
            return recipe.input <= input_inventory;
        }

        void process() {
        }
    };

    class Producer: public Machine{
        explicit Producer(const Recipe &recipe) : Machine(recipe) {
            // input = {};
        }
    };

    class Consumer : public Machine {

        explicit Consumer(const Recipe &recipe) : Machine(recipe) {
            // output = {};
        }
    };

    class Conveyor: public Machine {
    public:
        explicit Conveyor() : Machine(NoneVoid) {}

        void tick() override {
            Entity::tick();

            output_inventory += input_inventory;
            input_inventory.clear();
        }

    };

    class Connection: public Entity {
    public:
        Connection(Machine& in, Machine& out) : input(in), output(out)  {}

        void tick() override {
            Entity::tick();
            output.load(input.unload());
        }
    protected:
        Machine& input;
        Machine& output;
    private:
    };

}
