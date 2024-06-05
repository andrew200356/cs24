#include "VoxMap.h"

#include <algorithm>
#include <cmath>
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

// Heuristic function for A* (Manhattan distance)
double VoxMap::heuristic(const Point& a, const Point& b) const {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y) + std::abs(a.z - b.z);
}
// A* algorithm to find the route from src to dst
Route VoxMap::route(Point src, Point dst) {
    // Check if the source point is valid
    if (!isValidPoint(src)) {
        throw InvalidPoint(src);  // Throw an exception if the source point is invalid
    }

    // Check if the destination point is valid
    if (!isValidPoint(dst)) {
        throw InvalidPoint(dst);  // Throw an exception if the destination point is invalid
    }

    // Lambda function to generate a unique key for each point based on its coordinates
    auto toKey = [](const Point& p) {
        return std::to_string(p.x) + "," + std::to_string(p.y) + "," + std::to_string(p.z);
    };

    // Define the four possible horizontal movements (north, east, south, west)
    const std::vector<std::pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

    // Priority queue (min heap) prioritized by the estimated total cost (f = g + h) to reach the destination
    std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, std::greater<>> openSet;

    // Set to keep track of visited nodes
    std::unordered_set<std::string> closedSet;

    // Maps to store the cost of the shortest path from the start to each node, and to reconstruct the path
    std::unordered_map<std::string, double> gScore;
    std::unordered_map<std::string, Point> cameFrom;
    std::unordered_map<std::string, Move> moveFrom;

    // Initialize the gScore of the source node to 0 and add it to the open set with its heuristic cost
    gScore[toKey(src)] = 0.0;
    openSet.push({heuristic(src, dst), src});

    // Main loop of the A* algorithm
    while (!openSet.empty()) {
        // Get the node with the lowest estimated total cost (f = g + h)
        Point current = openSet.top().second;
        openSet.pop();

        // Check if the destination is reached
        if (current == dst) {
            Route path;
            // Reconstruct the path by tracing back from the destination to the source
            for (Point p = dst; p != src; p = cameFrom[toKey(p)]) {
                path.push_back(moveFrom[toKey(p)]);
            }
            std::reverse(path.begin(), path.end());
            return path;  // Return the reconstructed path
        }

        // Mark the current node as visited by adding it to the closed set
        closedSet.insert(toKey(current));

        // Explore all possible neighbors
        for (int i = 0; i < 4; ++i) {
            Point neighbor = {current.x + directions[i].first, current.y + directions[i].second, current.z};

            // Check if the neighbor point is valid or if adjustments are needed for falling or jumping
            if (isValidPoint(neighbor)) {
                // Neighbor is immediately valid, proceed with it
            } else if (!isValidPoint(neighbor) && neighbor.z < height - 1 && isValidPoint({neighbor.x, neighbor.y, neighbor.z + 1})) {
                // Handle jumping up one level if the neighbor point was not valid
                neighbor.z++;  // Jump up one level
            } else {
                // Handle falling if the neighbor point was not valid and we can't jump up
                while (!isValidPoint(neighbor) && neighbor.z > 0) {
                    neighbor.z--;  // Fall down
                }
            }

            // Skip the neighbor if it is not valid or has already been visited
            if (!isValidPoint(neighbor) || closedSet.find(toKey(neighbor)) != closedSet.end()) {
                continue;
            }

            // Calculate the tentative gScore for the neighbor
            double tentative_gScore = gScore[toKey(current)] + 1.0;
            // If the neighbor is not in gScore or the new path is better, update the path information
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
