#include "Tree.h"

// Tree Function Implementations
Tree::Tree() : root(nullptr){};

Tree::~Tree() {
    clear();
};

void Tree::clear() {
    // if the tree is empty, return
    if (root == nullptr) {
        return;
    }
    clearRecursively(root);
    root = nullptr;
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
    if (root == nullptr) {
        return 0;
    }
    return root->weight;
};

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
        if (s > current->data) {
            // if the item is greater than the current node, go to the right
            current->addOne();
            current = current->right;
        } else {
            // if the item is less than the current node, go to the left
            // if the item is already present in the tree(same), go to the left
            current->addOne();
            current = current->left;
        }
    }

    // now we have the parent node
    Node *newNode = new Node(s);
    newNode->addOne();
    if (parent == nullptr) {
        root = newNode;
    } else if (parent->data < s) {
        parent->right = newNode;
    } else {
        parent->left = newNode;
    }
};

std::string Tree::lookup(size_t index) const {
    // if the index is greater than the weight of the tree, throw an exception
    if (root == nullptr) {
        throw std::out_of_range("Index out of range");
    } else if (index >= root->weight) {
        throw std::out_of_range("Index out of range");
    }
    return nth_inorder(root, index);
};

std::string Tree::nth_inorder(Node *n, size_t wanted) const {
    if (n == nullptr)
        return "";

    // get the weight of the left subtree which is also the index of the root
    size_t leftWeight = n->left == nullptr ? 0 : n->left->weight;

    if (wanted < leftWeight) {
        // the item is in the left subtree
        return nth_inorder(n->left, wanted);
    } else if (wanted > leftWeight) {
        // the item is in the right subtree
        return nth_inorder(n->right, wanted - leftWeight - 1);
    } else {
        // the item is the root
        return n->data;
    }
}

void Tree::print() const {
    if (root == nullptr) {
        std::cout << "-" << std::endl;
    } else {
        printInorder(root);
        std::cout << std::endl;
    }
};

// Function to print inorder traversal
void Tree::printInorder(Node *node) const {
    if (node == nullptr) {
        // if the current subtree is null, return -
        std::cout << "-";
    } else if (node->weight == 1) {
        // if the current subtree is just itself (since weight is 1), print the data
        std::cout << node->data;
    } else {
        // if the current subtree is not null, print the left subtree
        std::cout << "(";
        printInorder(node->left);
        // print the data
        std::cout << " " << node->data << " ";
        // print the right subtree
        printInorder(node->right);
        std::cout << ")";
    }
};

void Tree::remove(size_t index){
    // if the index is greater than the weight of the tree, throw an exception
    if (root == nullptr) {
        throw std::out_of_range("Index out of range");
    } else if (index >= root->weight) {
        throw std::out_of_range("Index out of range");
    }
    // removeRecursively(root, index);
};

Node *Tree::getRoot() const {
    return root;
};

void Tree::getWeight(Node *n) {
    if (n == nullptr) {
        return;
    }
    getWeight(n->left);
    std::cout << "Weight of " << n->data << ": " << n->weight << std::endl;
    getWeight(n->right);
};