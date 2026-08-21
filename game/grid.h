#pragma once

#include <cmath>

/**
 * @brief Represents cardinal directions on the grid.
 */
enum Direction {
    north = 0,
    east,
    south,
    west
};

/**
 * @brief Represents a 2D integer coordinate point.
 */
struct Point2D {
    int x;
    int y;
};

constexpr Point2D NULL_POINT = {-99, -99};

/**
 * @brief Represents a 2D floating-point vector with basic vector operations.
 */
struct Vec2 {
    float x = 0.0f;
    float y = 0.0f;

    Vec2 operator+(const Vec2& o) const;
    Vec2 operator-(const Vec2& o) const;
    Vec2 operator*(float scalar) const;

    [[nodiscard]] float length_sq() const;
    [[nodiscard]] float length() const;
    [[nodiscard]] Vec2 normalized() const;
    [[nodiscard]] float angle_degrees() const;
    [[nodiscard]] float dot(const Vec2& o) const;
};

/**
 * @brief Calculates the displacement vector between two points.
 * @param a Start point.
 * @param b End point.
 * @return Vec2 representing the delta from a to b.
 */
Vec2 delta(Point2D a, Point2D b);

/**
 * @brief Converts an angle in degrees to a cardinal Direction.
 * @param deg Angle in degrees.
 * @return Corresponding Direction.
 */
Direction deg_direction(float deg);
