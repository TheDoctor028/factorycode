#include "grid.h"

#include <cmath>
#include <stdexcept>

Vec2 Vec2::operator+(const Vec2& o) const {
    return {x + o.x, y + o.y};
}

Vec2 Vec2::operator-(const Vec2& o) const {
    return {x - o.x, y - o.y};
}

Vec2 Vec2::operator*(float scalar) const {
    return {x * scalar, y * scalar};
}

float Vec2::length_sq() const {
    return x * x + y * y;
}

float Vec2::length() const {
    return std::sqrt(length_sq());
}

Vec2 Vec2::normalized() const {
    float len = length();
    return (len > 0.0f) ? Vec2{x / len, y / len} : Vec2{0.0f, 0.0f};
}

float Vec2::angle_degrees() const {
    constexpr float rad_to_deg = 180.0f / M_PI;
    return std::atan2(y, x) * rad_to_deg;
}

float Vec2::dot(const Vec2& o) const {
    return x * o.x + y * o.y;
}

Vec2 delta(Point2D a, Point2D b) {
    return { static_cast<float>(b.x - a.x), static_cast<float>(b.y - a.y) };
}

Direction deg_direction(const float deg) {
    if (deg == 90.0) return Direction::north;
    if (deg == 0.0) return Direction::east;
    if (deg == 180.0 || deg == -180.0) return Direction::south;
    if (deg == -90.0) return Direction::west;
    throw std::runtime_error("Deg cant be turned in to direction due its not matching any direction");
}

