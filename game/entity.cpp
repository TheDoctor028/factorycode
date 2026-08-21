#include "entity.h"

namespace factorycode {

    void Entity::tick() {
        if (sleeping && alarm-- == 0) sleeping = false;
    }

    bool Entity::is_placed() const {
        return placed;
    }

    void Entity::place(Point2D p) {
        placed = true;
        position = p;
    }

    void Entity::pickup() {
        placed = false;
        position = NULL_POINT;
    }

    void Entity::sleep(const uint dur) {
        alarm += dur;
        sleeping = true;
    }

    Point2D Entity::get_position() const {
        return position;
    }

}
