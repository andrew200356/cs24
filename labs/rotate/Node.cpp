#include "Node.h"

// Node Function Implementations
Node::Node(const std::string& s) : data(s), left(nullptr), right(nullptr){};

Node::Node(const std::string& s, Node* left, Node* right) {
    data = s;
    this->left = left;
    this->right = right;
};