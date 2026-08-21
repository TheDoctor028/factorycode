#pragma once

#include <set>
#include <unordered_map>
#include <utility>
#include <cmath>
#include <mdspan>

#include  "grid.h"
#include "wasmtime.hh"
#include "Material.h"
#include "recipe.h"

namespace factorycode {
    void debug(char* message);

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

        void place(Point2D p) {
            placed = true;
            position = p;
        }

        void pickup() {
            placed = false;
            position = NULL_POINT;
        }

        virtual void sleep(const uint dur) {
            alarm += dur;
            sleeping = true;
        }

        [[nodiscard]]
        Point2D get_position() const {
            return position;
        }
    protected:
        Point2D position = NULL_POINT;
        bool placed = false;
        uint alarm = 0;
        bool sleeping = false;
    };

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

    class Consumer : Machine {
        explicit Consumer(const Recipe &recipe) : Machine(recipe) {
            // output = {};
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

        void place(Entity& entity, const Point2D p) {
            // Check that its free
            map.set(p.x, p.y, &entity);
            entity.place(p);
        }

        bool connectMachines(Machine& ent1, Machine& ent2) {
            // Check if both entity is placed

            if (!ent1.is_placed() || !ent2.is_placed()) return false;
            const Vec2 d = delta(ent1.get_position(), ent2.get_position());
            const Direction dir = deg_direction(d.angle_degrees());

            if (const float r = d.length(); r == 1.0) {
                const auto conn = Connection(ent1, ent2);
                entities.push_back(conn);
                return true;
            }
            return false;
        }

    protected:
        wasmtime::Engine wasm_engine;
        wasmtime::Store wasm_store;


        int credit = 0;
        uint m_tick = 0;

        bool paused = false;

        std::unordered_map<Material, uint> inventory;

        std::vector<Entity> entities;
        Map map;

        private:
    };
}
