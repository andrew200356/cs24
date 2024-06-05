
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
    // Priority queue(min heap), prioritized by their estimated total cost (f = g + h) to reach the destination
    std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, std::greater<>> openSet;
    std::unordered_set<std::string> closedSet;
    std::unordered_map<std::string, double> gScore;
    std::unordered_map<std::string, Point> cameFrom;
    std::unordered_map<std::string, Move> moveFrom;

    gScore[toKey(src)] = 0.0;
    openSet.push({heuristic(src, dst), src});

    // main loop
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

        // Check all neighbors, and add them to the openset if they are valid
        for (int i = 0; i < 4; ++i) {
            Point neighbor = {current.x + directions[i].first, current.y + directions[i].second, current.z};
            // std::cout << "Checking neighbor " << neighbor << std::endl;

            // after moving, check if the point is valid
            // a point is valid if it is valid point and
            // if we can jump up one level or fall down to the next level

            if (isValidPoint(neighbor)) {
                // Neighbor is immediately valid, proceed with it
            } else if (!isValidPoint(neighbor) && neighbor.z < height - 1 && isValidPoint({neighbor.x, neighbor.y, neighbor.z + 1})) {
                // Handle jumping up one level if the neighbor point was not valid
                neighbor.z++;  // Jump up one level
                // std::cout << "Jumping up to " << neighbor << std::endl;
            } else {
                // Handle falling if the neighbor point was not valid and we can't jump up
                while (!isValidPoint(neighbor) && neighbor.z > 0) {
                    neighbor.z--;  // Fall down
                    // std::cout << "Falling down from " << neighbor << std::endl;
                }
            }

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