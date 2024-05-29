#include "VoxMap.h"

#include <queue>
#include <sstream>
#include <stdexcept>
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
    return p.x >= 0 && p.x < width && p.y >= 0 && p.y < depth && p.z >= 0 && p.z < height &&
           !map[p.z][p.y][p.x] && (p.z == 0 || map[p.z - 1][p.y][p.x]);
}

// Find the route from src to dst
Route VoxMap::route(Point src, Point dst) {
    if (!isValidPoint(src)) {
        throw InvalidPoint(src);
    }
    if (!isValidPoint(dst)) {
        throw InvalidPoint(dst);
    }

    const std::vector<std::pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    std::unordered_set<std::string> visited;
    std::queue<std::pair<Point, Route>> q;
    q.push({src, {}});
    visited.insert(std::to_string(src.x) + "," + std::to_string(src.y) + "," + std::to_string(src.z));

    while (!q.empty()) {
        auto [current, path] = q.front();
        q.pop();

        if (current.x == dst.x && current.y == dst.y && current.z == dst.z) {
            return path;
        }

        for (int i = 0; i < 4; ++i) {
            Point next = {current.x + directions[i].first, current.y + directions[i].second, current.z};
            while (next.z > 0 && !isValidPoint(next)) {
                next.z--;
            }
            while (next.z < height - 1 && isValidPoint({next.x, next.y, next.z + 1})) {
                next.z++;
            }
            std::string key = std::to_string(next.x) + "," + std::to_string(next.y) + "," + std::to_string(next.z);
            if (isValidPoint(next) && visited.find(key) == visited.end()) {
                visited.insert(key);
                Route newPath = path;
                newPath.push_back(static_cast<Move>(i));
                q.push({next, newPath});
            }
        }
    }

    throw NoRoute(src, dst);
}
