#include "VoxMap.h"

#include <algorithm>
#include <cmath>
#include <map>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

#include "Errors.h"

// Constructor to initialize the map from an input stream
VoxMap::VoxMap(std::istream& stream) {
    stream >> width >> depth >> height;
    map.resize(height, std::vector<std::vector<bool>>(depth, std::vector<bool>(width, false)));
    std::string temp;
    std::getline(stream, temp);

    for (int z = 0; z < height; ++z) {
        std::string line;
        std::getline(stream, line);  // Skip the empty line
        for (int y = 0; y < depth; ++y) {
            std::getline(stream, line);
            for (int x = 0; x < width / 4; ++x) {
                char hexChar = line[x];
                int hexValue = (hexChar >= '0' && hexChar <= '9') ? hexChar - '0' : hexChar - 'A' + 10;
                for (int bit = 3; bit >= 0; --bit) {
                    map[z][y][4 * x + (3 - bit)] = (hexValue & (1 << bit)) != 0;
                }
            }
        }
    }
}

// Destructor
VoxMap::~VoxMap() {
    // Nothing to clean up, vectors handle their own memory
}

// Helper function to check if a point is valid
inline bool VoxMap::isValidPoint(const Point& p) const {
    return p.x >= 0 && p.x < width && p.y >= 0 && p.y < depth && p.z > 0 && p.z < height  // Check if the point is within bounds (z > 0 to avoid falling off the map)
           && !map[p.z][p.y][p.x]                                                         // Check if the point is not an obstacle
           && (p.z == 0 || map[p.z - 1][p.y][p.x]);                                       // Check if the point is not floating
}

// Helper function to check if a point is valid upper point
inline bool VoxMap::inBound(const Point& p) const {
    return p.x >= 0 && p.x < width && p.y >= 0 && p.y < depth && p.z > 0 && p.z < height;  // Check if the point is within bounds (z > 0 to avoid falling off the map)
}

Point VoxMap::fall(Point point) const {
    while (point.z > 0 && !map[point.z - 1][point.y][point.x]) {
        point.z--;
    }
    if (point.z == 0 || (point.z == 1 && !map[0][point.y][point.x])) {
        point.z = -1;  // Mark as invalid
    }
    return point;
}

Point VoxMap::jump(Point point) const {
    if (point.z < height - 1 && !map[point.z + 1][point.y][point.x]) {
        point.z++;
        return point;
    }
    point.z = -1;  // Mark as invalid if jump is not possible
    return point;
}

// Heuristic function for A* (Manhattan distance)
double VoxMap::heuristic(const Point& a, const Point& b) const {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

auto toKey = [](const Point& p) {
    return std::to_string(p.x) + "," + std::to_string(p.y) + "," + std::to_string(p.z);
};

// A* algorithm to find the route from src to dst
Route VoxMap::route(Point src, Point dst) {
    if (!isValidPoint(src)) {
        throw InvalidPoint(src);
    }
    if (!isValidPoint(dst)) {
        throw InvalidPoint(dst);
    }

    const std::vector<std::pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, std::greater<>> openSet;
    std::unordered_set<Point, PointHash> closedSet;
    std::unordered_map<Point, double, PointHash> gScore;
    std::unordered_map<Point, Point, PointHash> cameFrom;
    std::unordered_map<Point, Move, PointHash> moveFrom;

    gScore[src] = 0.0;
    openSet.push({heuristic(src, dst), src});

    while (!openSet.empty()) {
        Point current = openSet.top().second;
        openSet.pop();

        if (current == dst) {
            return reconstructPath(src, dst, cameFrom, moveFrom);
        }

        closedSet.insert(current);
        exploreNeighbors(current, directions, openSet, closedSet, gScore, cameFrom, moveFrom, dst);
    }

    throw NoRoute(src, dst);
}

Route VoxMap::reconstructPath(const Point& src, const Point& dst,
                              const std::unordered_map<Point, Point, PointHash>& cameFrom,
                              const std::unordered_map<Point, Move, PointHash>& moveFrom) const {
    Route path;
    for (Point p = dst; p != src; p = cameFrom.at(p)) {
        path.push_back(moveFrom.at(p));
    }
    std::reverse(path.begin(), path.end());
    return path;
}

void VoxMap::exploreNeighbors(const Point& current,
                              const std::vector<std::pair<int, int>>& directions,
                              std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, std::greater<>>& openSet,
                              std::unordered_set<Point, PointHash>& closedSet,
                              std::unordered_map<Point, double, PointHash>& gScore,
                              std::unordered_map<Point, Point, PointHash>& cameFrom,
                              std::unordered_map<Point, Move, PointHash>& moveFrom,
                              const Point& dst) const {
    for (int i = 0; i < 4; ++i) {
        Point neighbor = {current.x + directions[i].first, current.y + directions[i].second, current.z};

        if (!inBound(neighbor)) {
            continue;
        }

        if (!map[neighbor.z][neighbor.y][neighbor.x]) {
            if (neighbor.z > 0 && !map[neighbor.z - 1][neighbor.y][neighbor.x]) {
                neighbor = fall(neighbor);
                if (neighbor.z == -1) continue;
            }
        } else {
            if (inBound({current.x, current.y, current.z + 1}) && map[current.z + 1][current.y][current.x]) {
                continue;
            }
            if (inBound({neighbor.x, neighbor.y, neighbor.z + 1}) && map[neighbor.z + 1][neighbor.y][neighbor.x]) {
                continue;
            }
            neighbor = jump(neighbor);
            if (neighbor.z == -1) continue;
        }

        if (!isValidPoint(neighbor) || closedSet.find(neighbor) != closedSet.end()) {
            continue;
        }

        double tentative_gScore = gScore[current] + 1.0;
        if (gScore.find(neighbor) == gScore.end() || tentative_gScore < gScore[neighbor]) {
            cameFrom[neighbor] = current;
            moveFrom[neighbor] = static_cast<Move>(i);
            gScore[neighbor] = tentative_gScore;
            openSet.push({tentative_gScore + heuristic(neighbor, dst), neighbor});
        }
    }
}
