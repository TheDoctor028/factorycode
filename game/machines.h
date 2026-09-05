#pragma once

#include <sys/types.h>

#include "entity.h"
#include "material.h"
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

        static std::string staticEntityType() {
            return "Machine";
        }

        [[nodiscard]]
        std::string entityType() const override {
            return staticEntityType();
        }

    protected:
        MaterialStackList input_inventory;
        MaterialStackList inventory;
        MaterialStackList output_inventory;

        uint progress = 0;

        virtual bool can_craft();

        void process();
    };

    /**
     * @brief Producer machine that produces resources.
     */
    class Producer : public Machine {
    public:

        explicit Producer(const Recipe& recipe);

        static std::string staticEntityType() {
            return "Producer";
        }

        [[nodiscard]]
        std::string entityType() const override {
            return staticEntityType();
        }
    protected:
        bool can_craft() override;
    };

    /**
     * @brief Consumer machine that consumes resources.
     */
    class Consumer : public Machine {
    public:
        explicit Consumer(const Recipe& recipe);

        static std::string staticEntityType() {
            return "Consumer";
        }

        [[nodiscard]]
        std::string entityType() const override {
            return staticEntityType();
        }
    };

    /**
     * @brief Conveyor machine that transfers items.
     */
    class Conveyor : public Machine {
    public:
        explicit Conveyor();

        void tick() override;

        static std::string staticEntityType() {
            return "Conveyor";
        }

        [[nodiscard]]
        std::string entityType() const override {
            return staticEntityType();
        }
    };

    /**
     * @brief Connection entity transferring materials between two machines.
     */
    class Connection : public Entity {
    public:
        Connection(Machine& in, Machine& out);

        void tick() override;

        static std::string staticEntityType() {
            return "Connection";
        }

        [[nodiscard]]
        std::string entityType() const override {
            return staticEntityType();
        }

    protected:
        Machine& input;
        Machine& output;
    };

}
