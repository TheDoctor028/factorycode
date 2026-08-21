#include "entity.h"
#include "logging.h"

#include <string>

namespace factorycode {

    void Entity::tick() {
        if (sleeping) {
            if (alarm-- == 0) {
                sleeping = false;
                debug("[" + entityType() + "] Woke up at position " + to_string(position));
            }
        }
    }

    bool Entity::is_placed() const {
        return placed;
    }

    void Entity::place(Point2D p) {
        placed = true;
        position = p;
        debug("[" + entityType() + "] Placed at " + to_string(p));
    }

    void Entity::pickup() {
        debug("[" + entityType() + "] Picked up from " + to_string(position));
        placed = false;
        position = NULL_POINT;
    }

    void Entity::sleep(const uint dur) {
        alarm += dur;
        sleeping = true;
        debug("[" + entityType() + "] Sleeping for " + std::to_string(dur) +
              " ticks at " + to_string(position));
    }

    Point2D Entity::get_position() const {
        return position;
    }

}
