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
bool VoxMap::isValidPoint(const Point& p) const {
    return p.x >= 0 && p.x < width && p.y >= 0 && p.y < depth && p.z > 0 && p.z < height  // Check if the point is within bounds (z > 0 to avoid falling off the map)
           && !map[p.z][p.y][p.x]                                                         // Check if the point is not an obstacle
           && (p.z == 0 || map[p.z - 1][p.y][p.x]);                                       // Check if the point is not floating
}

// Helper function to check if a point is valid upper point
bool VoxMap::inBound(const Point& p) const {
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

// A* algorithm to find the route from src to dst
Route VoxMap::route(Point src, Point dst) {
    if (!isValidPoint(src)) {
        throw InvalidPoint(src);  // Throw an exception if the source point is invalid
    }
    if (!isValidPoint(dst)) {
        throw InvalidPoint(dst);  // Throw an exception if the destination point is invalid
    }

    auto toKey = [](const Point& p) {
        return std::to_string(p.x) + "," + std::to_string(p.y) + "," + std::to_string(p.z);
    };

    const std::vector<std::pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, std::greater<>> openSet;
    std::unordered_set<std::string> closedSet;
    std::map<std::string, double> gScore;
    std::map<std::string, Point> cameFrom;
    std::map<std::string, Move> moveFrom;

    gScore[toKey(src)] = 0.0;
    openSet.push({heuristic(src, dst), src});

    // Main loop of the A* algorithm
    while (!openSet.empty()) {
        Point current = openSet.top().second;
        openSet.pop();

        // Check if the destination is reached
        if (current == dst) {
            Route path;
            for (Point p = dst; p != src; p = cameFrom[toKey(p)]) {
                path.push_back(moveFrom[toKey(p)]);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        closedSet.insert(toKey(current));

        // Explore all possible neighbors
        for (int i = 0; i < 4; ++i) {
            Point neighbor = {current.x + directions[i].first, current.y + directions[i].second, current.z};

            // Check if the move is valid
            // Check bounds
            if (!inBound(neighbor)) {
                continue;
            }
            // std::cout << "Neighbor: " << neighbor << std::endl;
            // Check if the neighbor is an obstacle
            if (!map[neighbor.z][neighbor.y][neighbor.x]) {
                // Check if the neighbor is floating and needs to fall
                if (neighbor.z > 0 && !map[neighbor.z - 1][neighbor.y][neighbor.x]) {
                    neighbor = fall(neighbor);
                    if (neighbor.z == -1) continue;  // If falling is not possible, continue to the next neighbor
                }
            } else {
                // Check for jump if the neighbor is an obstacle
                if (inBound({current.x, current.y, current.z + 1}) && map[current.z + 1][current.y][current.x]) {
                    continue;  // Skip if there's a block directly above the current position
                }
                if (inBound({neighbor.x, neighbor.y, neighbor.z + 1}) && map[neighbor.z + 1][neighbor.y][neighbor.x]) {
                    continue;  // Skip if there's a block directly above the neighbor position
                }

                // Perform the jump
                neighbor = jump(neighbor);
                if (neighbor.z == -1) continue;  // If jumping is not possible, continue to the next neighbor
            }

            // Skip the neighbor if it is not valid or has already been visited
            if (!isValidPoint(neighbor) || closedSet.find(toKey(neighbor)) != closedSet.end()) {
                continue;
            }

            double tentative_gScore = gScore[toKey(current)] + 1.0;
            if (gScore.find(toKey(neighbor)) == gScore.end() || tentative_gScore < gScore[toKey(neighbor)]) {
                cameFrom[toKey(neighbor)] = current;
                moveFrom[toKey(neighbor)] = static_cast<Move>(i);
                gScore[toKey(neighbor)] = tentative_gScore;
                openSet.push({tentative_gScore + heuristic(neighbor, dst), neighbor});
            }
        }
    }

    throw NoRoute(src, dst);  // Throw an exception if no route is found
}
