#ifndef VOXMAP_H
#define VOXMAP_H

#include <istream>
#include <vector>

#include "Point.h"
#include "Route.h"

class VoxMap {
    // Member Variables
    int width, depth, height;
    std::vector<std::vector<std::vector<bool>>> map;

    // Helper Functions
    bool isValidPoint(const Point& p) const;
    bool inBound(const Point& p) const;
    double heuristic(const Point& a, const Point& b) const;

   public:
    VoxMap(std::istream& stream);
    ~VoxMap();

    Route route(Point src, Point dst);
};

#endif
