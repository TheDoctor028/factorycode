#pragma once

#include <sys/types.h>

#include "entity.h"
#include "Material.h"
#include "recipe.h"

namespace factorycode {

    /**
     * @brief Represents a machine that crafts items according to a recipe.
     */
    class Machine : public Entity {
    public:
        explicit Machine(Recipe recipe);
        const Recipe recipe;

        void tick() override;

        /**
         * @brief Unloads output inventory materials.
         * @return MaterialStackList containing the output materials.
         */
        MaterialStackList unload();

        /**
         * @brief Loads materials into the input inventory.
         * @param materials Materials to load.
         */
        void load(const MaterialStackList& materials);

    protected:
        MaterialStackList input_inventory;
        MaterialStackList inventory;
        MaterialStackList output_inventory;

        uint progress = 0;

        bool can_craft();

        void process();
    };

    /**
     * @brief Producer machine that produces resources.
     */
    class Producer : public Machine {
    public:
        explicit Producer(const Recipe& recipe);
    };

    /**
     * @brief Consumer machine that consumes resources.
     */
    class Consumer : public Machine {
    public:
        explicit Consumer(const Recipe& recipe);
    };

    /**
     * @brief Conveyor machine that transfers items.
     */
    class Conveyor : public Machine {
    public:
        explicit Conveyor();

        void tick() override;
    };

    /**
     * @brief Connection entity transferring materials between two machines.
     */
    class Connection : public Entity {
    public:
        Connection(Machine& in, Machine& out);

        void tick() override;

    protected:
        Machine& input;
        Machine& output;
    };

}
