#include "Game.h"
#include "logging.h"

#include <stdexcept>

namespace factorycode {

    Map::Map(const uint x, const uint y) : size_x(x), size_y(y) {
        for (int i_x = 0; i_x < size_x; i_x++) {
            for (int i_y = 0; i_y < size_y; i_y++) {
                map.insert(map.end(), std::vector<Entity*>());
                map[i_x].insert(map[i_x].end(), nullptr);
            }
        }
    }

    Entity* Map::get(const uint x, const uint y) const {
        if (x > size_x || y > size_y) {
            error("[Map] Coordinates (" + std::to_string(x) + ", " + std::to_string(y) +
                  ") out of boundaries (" + std::to_string(size_x) + ", " + std::to_string(size_y) + ")");
            throw std::runtime_error("x or y coordinates are out of boundaries.");
        }

        return map.at(x).at(y);
    }

    void Map::set(const uint x, const uint y, Entity* entity) {
        if (x > size_x || y > size_y) {
            error("[Map] Coordinates (" + std::to_string(x) + ", " + std::to_string(y) +
                  ") out of boundaries (" + std::to_string(size_x) + ", " + std::to_string(size_y) + ")");
            throw std::runtime_error("x or y coordinates are out of boundaries.");
        }

        map.at(x).at(y) = entity;
    }

    Game::Game() : wasm_store(wasm_engine), map(10, 10) {
        info("[Game] Initialized game engine with map size (10, 10)");
    }

    void Game::tick() {
        info("[Game] Starting tick " + std::to_string(m_tick));
        for (auto& entity : entities) {
            entity.tick();
        }

        m_tick++;
        info("[Game] Finished tick " + std::to_string(m_tick - 1));
    }

    void Game::place(Entity& entity, const Point2D p) {
        map.set(p.x, p.y, &entity);
        entity.place(p);
        info("[Game] Placed entity at " + to_string(p));
    }

    bool Game::connectMachines(Machine& ent1, Machine& ent2) {
        if (!ent1.is_placed() || !ent2.is_placed()) {
            warn("[Game] Cannot connect machines: one or both machines are not placed.");
            return false;
        }
        const Vec2 d = delta(ent1.get_position(), ent2.get_position());
        const Direction dir = deg_direction(d.angle_degrees());

        if (const float r = d.length(); r == 1.0) {
            const auto conn = Connection(ent1, ent2);
            entities.push_back(conn);
            info("[Game] Connected machine at " + to_string(ent1.get_position()) +
                 " to machine at " + to_string(ent2.get_position()) +
                 " in direction " + to_string(dir));
            return true;
        }
        warn("[Game] Cannot connect machines: distance is not 1.0 (distance=" +
             std::to_string(d.length()) + ")");
        return false;
    }

}
