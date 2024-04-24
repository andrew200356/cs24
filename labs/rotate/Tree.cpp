#include "Tree.h"

#include <iostream>
#include <stdexcept>

// Tree Function Implementations
Tree::Tree() : root(nullptr), list_size(0){};

Tree::~Tree() {
    clear();
};

void Tree::clear() {
    clearRecursively(root);
    root = nullptr;
    list_size = 0;
};

void Tree::clearRecursively(Node* n) {
    if (n == nullptr) {
        return;
    }
    clearRecursively(n->left);
    clearRecursively(n->right);
    delete n;
};

size_t Tree::count() const {
    return list_size;
};

bool Tree::contains(const std::string& s) const {
    size_t max_val = ~0;
    return find(s) != max_val;
};

size_t Tree::find(const std::string& s) const {
    Node* current = root;
    size_t index = 0;

    // the code is triversal with in-order
    while (current != nullptr) {
        if (current->data == s) {
            // if the current node's data is equal to s, return the index
            // if there are multiple copies of the item, it returns the smallest index
            return index;
        } else if (current->data < s) {
            current = current->right;
        } else {
            current = current->left;
        }
        index++;
    }
    return ~0;
};

void Tree::insert(const std::string& s) {
    // do it with recursion
    Node* current = root;
    Node* parent = nullptr;
    while (current != nullptr) {
        parent = current;
        if (current->data < s) {
            current = current->right;
        } else {
            // if the item is already present in the tree, you will encounter it on your way down to a leaf node
            current = current->left;
        }
    }

    // now we have the parent node
    Node* newNode = new Node(s);
    if (parent == nullptr) {
        root = newNode;
    } else if (parent->data < s) {
        parent->right = newNode;
    } else {
        parent->left = newNode;
    }
};

std::string Tree::lookup(size_t index) const {
    if (index >= list_size) {
        throw std::out_of_range("Index out of range");
    }
    Node* current = root;
    size_t current_index = 0;
    while (current != nullptr) {
        if (current_index == index) {
            return current->data;
        } else if (current_index < index) {
            current = current->right;
        } else {
            current = current->left;
        }
    }
    return "";
};

void Tree::print() const {
    if (root == nullptr) {
        std::cout << "Empty Tree" << std::endl;
    } else {
        printInorder(root);
        std::cout << std::endl;
    }
};

// Function to print inorder traversal
void Tree::printInorder(Node* node) const {
    if (node == NULL)
        return;

    // First recur on left subtree
    printInorder(node->left);

    // Now deal with the node
    std::cout << node->data << " ";

    // Then recur on right subtree
    printInorder(node->right);
}

void Tree::remove(size_t index) {
    if (index >= list_size) {
        throw std::out_of_range("Index out of range");
    }
    Node* current = root;
    Node* parent = nullptr;
    size_t current_index = 0;
    while (current != nullptr) {
        if (current_index == index) {
            break;
        } else if (current_index < index) {
            parent = current;
            current = current->right;
        } else {
            parent = current;
            current = current->left;
        }
        current_index++;
    }

    // now we have the current node
    if (current->left == nullptr && current->right == nullptr) {
        // if the item to be removed is on a leaf node, simply remove it.
        if (parent == nullptr) {
            root = nullptr;
        } else if (parent->left == current) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
        delete current;
    } else if (current->left == nullptr || current->right == nullptr) {
        // if the item to be removed is on a node with one child, that child takes the node's place.
        Node* child = current->left == nullptr ? current->right : current->left;
        if (parent == nullptr) {
            root = child;
        } else if (parent->left == current) {
            parent->left = child;
        } else {
            parent->right = child;
        }
        delete current;
    } else {
        // if the item is on a node with two children, find the node n that contains the item at the next greater index.
        // Swap the values of the two nodes and remove node n. Node n is guaranteed to have one or zero children.
        Node* n = current->right;
        Node* n_parent = current;
        while (n->left != nullptr) {
            n_parent = n;
            n = n->left;
        }
        current->data = n->data;
        if (n_parent->left == n) {
            n_parent->left = n->right;
        } else {
            n_parent->right = n->right;
        }
        delete n;
    }
};

// remove with recursion
