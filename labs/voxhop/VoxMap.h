#ifndef VOXMAP_H
#define VOXMAP_H

#include <istream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
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
    Point jump(Point point) const;
    Point fall(Point point) const;
    Route reconstructPath(const Point& src, const Point& dst, const std::unordered_map<std::string, Point>& cameFrom, const std::unordered_map<std::string, Move>& moveFrom) const;
    void exploreNeighbors(const Point& current, const std::vector<std::pair<int, int>>& directions, std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, std::greater<>>& openSet, std::unordered_set<std::string>& closedSet, std::unordered_map<std::string, double>& gScore, std::unordered_map<std::string, Point>& cameFrom, std::unordered_map<std::string, Move>& moveFrom, const Point& dst) const;
    double heuristic(const Point& a, const Point& b) const;

   public:
    VoxMap(std::istream& stream);
    ~VoxMap();

    Route route(Point src, Point dst);
};

#endif
