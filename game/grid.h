#pragma once

#include <cmath>

enum Direction {
    north = 0,
    east,
    south,
    west
};

struct Point2D {
    int x;
    int y;
};

constexpr Point2D NULL_POINT = {-99, -99};

struct Vec2 {
    float x = 0.0f;
    float y = 0.0f;

    Vec2 operator+(const Vec2& o) const { return {x + o.x, y + o.y}; }
    Vec2 operator-(const Vec2& o) const { return {x - o.x, y - o.y}; }
    Vec2 operator*(float scalar)  const { return {x * scalar, y * scalar}; }

    [[nodiscard]] float length_sq() const { return x * x + y * y; }
    [[nodiscard]] float length()    const { return std::sqrt(length_sq()); }

    [[nodiscard]] Vec2 normalized() const {
        float len = length();
        return (len > 0.0f) ? Vec2{x / len, y / len} : Vec2{0.0f, 0.0f};
    }

    // Angle in degrees from the +X axis (-180° to +180°)
    [[nodiscard]] float angle_degrees() const {
        constexpr float rad_to_deg = 180.0f / M_PI;
        return std::atan2(y, x) * rad_to_deg;
    }

    [[nodiscard]] float dot(const Vec2& o) const { return x * o.x + y * o.y; }
};

Vec2 delta(Point2D a, Point2D b);

Direction deg_direction(const float deg);