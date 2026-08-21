#pragma once

#include <unordered_map>
#include <vector>
#include <sys/types.h>

#include "grid.h"
#include "wasmtime.hh"
#include "Material.h"
#include "entity.h"
#include "machines.h"

namespace factorycode {
    void debug(char* message);

    /**
     * @brief 2D Grid map of entities.
     */
    class Map {
    public:
        Map(const uint x, const uint y);

        const uint size_x;
        const uint size_y;

        [[nodiscard]]
        Entity* get(const uint x, const uint y) const;

        void set(const uint x, const uint y, Entity* entity);

    protected:
        std::vector<std::vector<Entity*>> map;
    };

    /**
     * @brief Main Game engine orchestrating entities, ticks, and wasm runtime.
     */
    class Game {
    public:
        // TODO dynamic map size
        Game();

        void tick();

        void place(Entity& entity, const Point2D p);

        bool connectMachines(Machine& ent1, Machine& ent2);

    protected:
        wasmtime::Engine wasm_engine;
        wasmtime::Store wasm_store;

        int credit = 0;
        uint m_tick = 0;

        bool paused = false;

        std::unordered_map<Material, uint> inventory;

        std::vector<Entity> entities;
        Map map;
    };
}
