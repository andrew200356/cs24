#ifndef NODE_H
#define NODE_H

#include <string>

struct Node {
    // This is a Binary Search Tree Node
    std::string data;
    Node* left;
    Node* right;

    // Node Constructor
    Node(const std::string& s);
    Node(const std::string& s, Node* left, Node* right);
};

#endif
