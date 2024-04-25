#include "Node.h"

// Node Function Implementations
Node::Node(const std::string& s) : data(s), left(nullptr), right(nullptr){};

Node::Node(const std::string& s, Node* left, Node* right) {
    data = s;
    this->left = left;
    this->right = right;
};

void Node::addOne() {
    weight++;
};

size_t Node::height(Node* root) const {
    if (root == nullptr) {
        return 0;
    }
    size_t l = 1 + height(root->left);
    size_t r = 1 + height(root->right);
    return std::max(l, r);
};

bool Node::isBalanced(Node* root) {
    if (root == NULL) {
        return true;
    }

    int leftheight = height(root->left);
    int rightheight = height(root->right);

    if (abs(leftheight - rightheight) > 1) {
        return false;
    }

    bool leftAns = isBalanced(root->left);
    bool rightAns = isBalanced(root->right);

    return (leftAns && rightAns);
}