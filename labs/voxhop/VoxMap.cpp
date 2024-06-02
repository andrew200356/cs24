#include "VoxMap.h"

#include <algorithm>
#include <cmath>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

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
bool VoxMap::isValidPoint(const Point& p) const {
    return p.x >= 0 && p.x < width && p.y >= 0 && p.y < depth && p.z > 0 && p.z < height  // Check if the point is within bounds (z > 0 to avoid falling off the map)
           && !map[p.z][p.y][p.x]                                                         // Check if the point is not an obstacle
           && (p.z == 0 || map[p.z - 1][p.y][p.x]);                                       // Check if the point is not floating
}

// Heuristic function for A* (Manhattan distance)
double VoxMap::heuristic(const Point& a, const Point& b) const {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

// A* algorithm to find the route from src to dst
Route VoxMap::route(Point src, Point dst) {
    if (!isValidPoint(src)) {
        throw InvalidPoint(src);  // Throw an exception if the source point is invalid
    }
    if (!isValidPoint(dst)) {
        throw InvalidPoint(dst);  // Throw an exception if the destination point is invalid
    }

    const std::vector<std::pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, std::greater<>> openSet;
    std::unordered_map<std::string, double> gScore;
    std::unordered_map<std::string, Point> cameFrom;
    std::unordered_map<std::string, Move> moveFrom;

    auto toKey = [](const Point& p) { return std::to_string(p.x) + "," + std::to_string(p.y) + "," + std::to_string(p.z); };

    gScore[toKey(src)] = 0.0;
    openSet.push({heuristic(src, dst), src});

    while (!openSet.empty()) {
        Point current = openSet.top().second;
        openSet.pop();

        if (current.x == dst.x && current.y == dst.y && current.z == dst.z) {
            Route path;
            for (Point p = dst; p != src; p = cameFrom[toKey(p)]) {
                path.push_back(moveFrom[toKey(p)]);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (int i = 0; i < 4; ++i) {
            Point neighbor = {current.x + directions[i].first, current.y + directions[i].second, current.z};

            // Check if we can move in the z direction
            if (neighbor.z > 0 && isValidPoint(neighbor)) {
                while (neighbor.z > 0 && !isValidPoint(neighbor)) {
                    neighbor.z--;  // Fall down
                }
                while (neighbor.z < height - 1 && isValidPoint({neighbor.x, neighbor.y, neighbor.z + 1})) {
                    neighbor.z++;  // Jump up
                }
                std::string neighborKey = toKey(neighbor);
                double tentative_gScore = gScore[toKey(current)] + 1.0;
                if (tentative_gScore < gScore[neighborKey] || gScore.find(neighborKey) == gScore.end()) {
                    cameFrom[neighborKey] = current;
                    moveFrom[neighborKey] = static_cast<Move>(i);
                    gScore[neighborKey] = tentative_gScore;
                    openSet.push({tentative_gScore + heuristic(neighbor, dst), neighbor});
                }
            }
        }
    }

    throw NoRoute(src, dst);  // Throw an exception if no route is found
}