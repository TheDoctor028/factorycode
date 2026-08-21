#pragma once

#include <unordered_map>
#include <mdspan>

#include  "grid.h"
#include "wasmtime.hh"
#include "Material.h"
#include "entity.h"
#include "machines.h"

namespace factorycode {
    void debug(char* message);

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
