#pragma once
#include <sys/types.h>
#include <string>

#include "grid.h"

namespace factorycode {
    /**
     * @brief Base class for placeable and tickable game entities.
     */
    class Entity {
    public:
        virtual ~Entity() = default;

        /**
         * @brief Updates entity state on game tick.
         */
        virtual void tick();

        /**
         * @brief Checks if the entity is currently placed on the map.
         * @return true if placed, false otherwise.
         */
        [[nodiscard]]
        bool is_placed() const;

        /**
         * @brief Places the entity at the given point.
         * @param p Position point.
         */
        void place(Point2D p);

        /**
         * @brief Picks up the entity from the map.
         */
        void pickup();

        /**
         * @brief Puts the entity to sleep for a duration of ticks.
         * @param dur Sleep duration in ticks.
         */
        virtual void sleep(const uint dur);

        /**
         * @brief Returns the current position of the entity.
         * @return Point2D position.
         */
        [[nodiscard]]
        Point2D get_position() const;

        /**
         * @brief Returns the static entity type name for Entity.
         * @return Static string representing entity type.
         */
        static std::string staticEntityType() {
            return "Entity";
        }

        /**
         * @brief Returns the entity type name of this instance.
         * @return String representing entity type.
         */
        [[nodiscard]]
        virtual std::string entityType() const {
            return staticEntityType();
        }

    protected:
        Point2D position = NULL_POINT;
        bool placed = false;
        uint alarm = 0;
        bool sleeping = false;
    };
}

