#pragma once

#include <set>
#include <unordered_map>
#include <utility>

#include "wasmtime.hh"
#include "materials.h"
#include "recipe.h"

namespace factorycode {
    void debug(char* message);

    enum Direction {
        north = 0,
        east,
        south,
        west
    };

    class Entity {
    public:
        virtual ~Entity() = default;

        virtual void tick() {
            if (sleeping && alarm-- == 0) sleeping = false;
        }

        [[nodiscard]]
        bool is_placed() const {
            return placed;
        }

        void set_placed(const bool state) {
            placed = state;
        }

        void sleep(const uint dur) {
            alarm += dur;
            sleeping = true;
        }
    protected:
        bool placed = false;
        uint alarm = 0;
        bool sleeping = false;
    };

    class Machine: Entity {
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
    protected:
        std::set<Machine*> inputs;
        std::set<Machine> outputs;

        MaterialStackList input_inventory;
        MaterialStackList inventory;
        MaterialStackList output_inventory;

        uint progress = 0;

        void load() {
            for (auto& input: inputs) {
                const auto mtl = input->unload();
                input_inventory += mtl;
            }
        }

        bool can_craft() {
            return recipe.input <= input_inventory;
        }

        void process() {
        }
    };

    class Producer: Machine {
        explicit Producer(const Recipe &recipe) : Machine(recipe) {
            // input = {};
        }
    };

    class Consumer: Machine {
        explicit Consumer(const Recipe &recipe) : Machine(recipe) {
            // output = {};
        }
    };

    class Map {
    public:
        Map(const uint x, const uint y): size_x(x), size_y(y) {
            for (int i_x = 0; i_x < size_x; i_x++) {
                for (int i_y = 0; i_y < size_y; i_y++) {
                    map.insert(map.end(), std::vector<Entity*>());
                    map[i_x].insert(map[i_x].end(), nullptr);
                }
            }
        }

        const uint size_x;
        const uint size_y;

        [[nodiscard]]
        Entity* get(const uint x, const uint y) const {
            if (x > size_x || y > size_y) throw std::runtime_error("x or y coordinates are out of boundaries.");

            return map.at(x).at(y);
        }

        void set(const uint x, const uint y, Entity* entity) {
            if (x > size_x || y > size_y) throw std::runtime_error("x or y coordinates are out of boundaries.");

            map.at(x).at(y) = entity;
        }

    protected:
        std::vector<std::vector<Entity*>> map;
    };

    class Game {
    public:
        // TODO dynamic map size
        Game() : wasm_store(wasm_engine), map(10, 10) {

        }

        void tick() {
            for (auto& entity : entities) {
                entity.tick();
            }

            m_tick++;
        }

        void place(Entity& entity) {
            map.set(0, 0, &entity);
            entity.set_placed(true);
        }

    protected:
        wasmtime::Engine wasm_engine;
        wasmtime::Store wasm_store;


        int credit = 0;
        uint m_tick = 0;

        bool paused = false;

        std::unordered_map<Materials, uint> inventory;

        std::vector<Entity> entities;
        Map map;

        private:
    };
}
