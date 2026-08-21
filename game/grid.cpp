#include "grid.h"

#include <stdexcept>

Vec2 delta(Point2D a, Point2D b) {
    return { static_cast<float>(a.x - b.x), static_cast<float>(a.y - b.y) };
}

Direction deg_direction(const float deg) {
    if (deg == 0.0) return Direction::north;
    if (deg == 90.0) return Direction::east;
    if (deg == 180.0) return Direction::south;
    if (deg == 270.0) return Direction::west;
    throw std::runtime_error("Deg cant be turned in to direction due its not matching any direction");
}

