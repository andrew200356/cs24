# WRITEUP.md

## Summary

The `voxhop` program reads a 3D voxel map of an island and performs route queries to find paths between two points on the island. It uses the A* algorithm to efficiently find paths, considering both horizontal and vertical movements, including jumping up and falling down.

### World Map Representation

The world map is represented in memory as a 3D vector of booleans. Each boolean value indicates whether a voxel is full (true) or empty (false). The map dimensions (width, depth, and height) are stored as integers.

### Route Query Algorithm

The program uses the A*algorithm to perform route queries. A* is chosen for its efficiency in finding the shortest path by considering both the actual cost from the start node and an estimated cost to the goal node. The heuristic used is the Manhattan distance in 3D.

#### Steps

1. **Initialization**:
   - Load the map dimensions and voxel data into a 3D vector.
   - Initialize data structures for the A* algorithm, including the open set (priority queue), closed set (unordered set), gScore (unordered map), cameFrom (unordered map), and moveFrom (unordered map).

2. **Main Loop**:
   - Extract the node with the lowest estimated total cost from the open set.
   - If the current node is the destination, reconstruct the path.
   - For each neighbor, check if the move is valid, considering vertical movements for jumping and falling.
   - Update the data structures if a better path is found.

3. **Path Reconstruction**:
   - Trace back from the destination to the source using the cameFrom map to reconstruct the path.

### Data Structures

- **3D Vector** (`std::vector<std::vector<std::vector<bool>>>`):
  - Represents the voxel map.
  - Chosen for its straightforward indexing and storage of voxel states.
- **Priority Queue** (`std::priority_queue<std::pair<double, Point>, std::vector<std::pair<double, Point>>, std::greater<>>`):
  - Stores nodes to be explored, prioritized by their estimated total cost.
  - Chosen for its efficient retrieval of the node with the lowest cost.
- **Unordered Set** (`std::unordered_set<std::string>`):
  - Keeps track of visited nodes.
  - Chosen for its efficient O(1) average-time complexity for lookups.
- **Unordered Map** (`std::unordered_map<std::string, double>`):
  - Stores the gScore (cost from start to node) and cameFrom (path reconstruction) information.
  - Chosen for its efficient O(1) average-time complexity for insertions and lookups.

### Big-O Runtime Analysis

- **Map Loading**: O(width*depth*height) - Reading and storing each voxel.
- **A* Initialization**: O(1) - Initializing data structures.
- **A* Main Loop**:
  - Each node expansion: O(log n) for priority queue operations.
  - Neighbor exploration: O(1) per neighbor.
  - Overall complexity: O(n log n), where n is the number of nodes.
- **Path Reconstruction**: O(k), where k is the length of the path.

### Gradescope Submission
