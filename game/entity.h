#pragma once
#include <sys/types.h>

#include "grid.h"


namespace factorycode {
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
}

