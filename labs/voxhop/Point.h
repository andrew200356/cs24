#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <tuple>

struct Point {
    int x;
    int y;
    int z;

    Point() {}
    Point(int x, int y, int z) : x(x), y(y), z(z) {}

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

    bool operator<(const Point& other) const {
        return std::tie(x, y, z) < std::tie(other.x, other.y, other.z);
    }

    bool operator>(const Point& other) const {
        return std::tie(x, y, z) > std::tie(other.x, other.y, other.z);
    }
};

std::istream& operator>>(std::istream& stream, Point& point);
std::ostream& operator<<(std::ostream& stream, const Point& point);

#endif
