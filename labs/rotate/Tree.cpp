#include "Tree.h"

// Tree Function Implementations
Tree::Tree() : root(nullptr), weight(0){};

Tree::~Tree() {
    clear();
};

void Tree::clear() {
    clearRecursively(root);
    root = nullptr;
    weight = 0;
};

void Tree::clearRecursively(Node *n) {
    if (n == nullptr) {
        return;
    }
    clearRecursively(n->left);
    clearRecursively(n->right);
    delete n;
};

size_t Tree::count() const {
    return weight;
};

size_t Tree::height(Node *n) const {
    if (n == nullptr) {
        return 0;
    }
    size_t l = 1 + height(root->left);
    size_t r = 1 + height(root->right);
    return std::max(l, r);
};

bool Tree::isBalanced(Node *root) {
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

bool Tree::contains(const std::string &s) const {
    size_t max_val = ~0;
    return find(s) != max_val;
};

size_t Tree::find(const std::string &s) const {
    Node *current = root;
    size_t index = 0;

    // the code is triversal with in-order
    return f_inorder(current, s, index);
};

size_t Tree::f_inorder(Node *n, const std::string &s, size_t &index) const {
    if (n == nullptr) {
        // Item is not found (base case)
        return ~0;
    }
    size_t foundIndex = f_inorder(n->left, s, index);  // Search the left subtree
    size_t a = ~0;
    if (foundIndex != a) {
        // Item is found in the left subtree
        return foundIndex;
    }
    if (s == n->data) {
        // Item is equal to the n's data, item is found
        return index;
    }
    index++;                               // Increment the index after visiting a node
    return f_inorder(n->right, s, index);  // Search the right subtree
}

void Tree::insert(const std::string &s) {
    // do it with recursion
    Node *current = root;
    Node *parent = nullptr;
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
    Node *newNode = new Node(s);
    if (parent == nullptr) {
        root = newNode;
    } else if (parent->data < s) {
        parent->right = newNode;
    } else {
        parent->left = newNode;
    }
    weight++;
};

std::string Tree::lookup(size_t index) const {
    if (index >= weight) {
        throw std::out_of_range("Index out of range");
    }
    return nth_inorder(root, 0, index);
};

std::string Tree::nth_inorder(Node *n, size_t index, size_t wanted) const {
    if (n == nullptr)
        return "";

    // first loop over the left subtree
    std::string left = nth_inorder(n->left, index, wanted);
    if (left != "") {
        return left;
    }

    // then check the middle
    if (index == wanted) {
        return n->data;
    }
    index++;

    // then loop over the right subtree
    return nth_inorder(n->right, index, wanted);
}

void Tree::print() const {
    if (root == nullptr) {
        std::cout << "Empty Tree" << std::endl;
    } else {
        printInorder(root);
        std::cout << std::endl;
    }
};

// Function to print inorder traversal
void Tree::printInorder(Node *node) const {
    if (node == nullptr)
        return;

    // First recur on left subtree
    printInorder(node->left);

    // Now deal with the node
    std::cout << node->data << " ";

    // Then recur on right subtree
    printInorder(node->right);
};

void Tree::remove(size_t index) {
    if (index >= weight) {
        throw std::out_of_range("Index out of range");
    }
    Node *current = root;
    Node *parent = nullptr;
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
        Node *child = current->left == nullptr ? current->right : current->left;
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
        Node *n = current->right;
        Node *n_parent = current;
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