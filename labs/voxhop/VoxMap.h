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

    struct PointHash {
        std::size_t operator()(const Point& p) const {
            // Use a combination of prime numbers for hashing
            return p.x * 73856093 ^ p.y * 19349663 ^ p.z * 83492791;
        }
    };

    // Helper Functions
    bool isValidPoint(const Point& p) const;
    bool inBound(const Point& p) const;
    Point jump(Point point) const;
    Point fall(Point point) const;
    double heuristic(const Point& a, const Point& b) const;

    Route reconstructPath(const Point& src, const Point& dst,
                          const std::unordered_map<Point, Point, PointHash>& cameFrom,
                          const std::unordered_map<Point, Move, PointHash>& moveFrom) const;  // Function to reconstruct the path

    void exploreNeighbors(const Point& current,
                          const std::vector<std::pair<int, int>>& directions,
                          std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, std::greater<>>& openSet,
                          std::unordered_set<Point, PointHash>& closedSet,
                          std::unordered_map<Point, double, PointHash>& gScore,
                          std::unordered_map<Point, Point, PointHash>& cameFrom,
                          std::unordered_map<Point, Move, PointHash>& moveFrom,
                          const Point& dst) const;  // Function to explore neighbors in the A* algorithm

   public:
    VoxMap(std::istream& stream);
    ~VoxMap();

    Route route(Point src, Point dst);
};

#endif
