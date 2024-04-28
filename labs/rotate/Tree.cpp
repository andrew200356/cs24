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
    root = insertRecursively(root, s);
}

Node* Tree::insertRecursively(Node* node, const std::string& item) {
    if (!node) {
        // Create a new node if the spot is found
        return new Node(item);
    }

    if (item < node->data) {
        // Recur to the left if the item is less than the current node's data
        node->left = insertRecursively(node->left, item);
    } else {
        // Recur to the right if the item is more or equal (handle duplicates as specified)
        node->right = insertRecursively(node->right, item);
    }

    // After insertion, update the weight of the node
    node->updateWeight();

    // Check rotations to balance the tree and perform them if necessary
    return balanceAfterInsert(node);
}

Node* Tree::balanceAfterInsert(Node* node) {
    if (!node) return node;

    // Check if we need a left rotation
    if (rotate_left(node)) {
        node = rotateLeft(node);
    }
    // Check if we need a right rotation
    else if (rotate_right(node)) {
        node = rotateRight(node);
    }

    return node;
}

Node* Tree::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    
    // Update weights after rotation
    x->updateWeight();
    y->updateWeight();
    
    return y;
}

Node* Tree::rotateRight(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    
    // Update weights after rotation
    y->updateWeight();
    x->updateWeight();
    
    return x;
}


void Tree::insertOld(const std::string &s) {
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

    // now we have the parent node of node we want to insert
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


bool Tree::rotate_left(Node *n) const {
    if (n == nullptr || n->right == nullptr) {
        return false;  // No rotation needed if the node or its right child is null.
    }
    size_t left_weight = n->left ? n->left->weight : 0;                     // x
    size_t right_l_weight = n->right->left ? n->right->left->weight : 0;    // y
    size_t right_r_weight = n->right->right ? n->right->right->weight : 0;  // z

    // Evaluate the balance before and after a left rotation.
    int current_imbalance = std::abs((int)(left_weight - (right_l_weight + right_r_weight + 1)));
    int new_imbalance = std::abs((int)((left_weight + right_l_weight + 1) - right_r_weight));

    // Rotate left if the new imbalance is less than the current imbalance.
    return new_imbalance < current_imbalance;
};

bool Tree::rotate_right(Node *n) const {
    if (n == nullptr || n->left == nullptr) {
        return false;  // No rotation needed if the node or its left child is null.
    }
    size_t left_l_weight = n->left->left ? n->left->left->weight : 0;    // x
    size_t left_r_weight = n->left->right ? n->left->right->weight : 0;  // y
    size_t right_weight = n->right ? n->right->weight : 0;               // z

    // Evaluate the balance before and after a right rotation.
    int current_imbalance = std::abs((int)((left_l_weight + left_r_weight + 1) - right_weight));
    int new_imbalance = std::abs((int)(left_r_weight + 1 + right_weight - left_l_weight));

    // Rotate right if the new imbalance is less than the current imbalance.
    return new_imbalance < current_imbalance;
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

void Tree::remove(size_t index) {
    // if the index is greater than the weight of the tree, throw an exception
    if (root == nullptr) {
        throw std::out_of_range("Index out of range");
    } else if (index >= root->weight) {
        throw std::out_of_range("Index out of range");
    }
    removeRecursively(root, index);
};

void Tree::removeRecursively(Node *&n, size_t index) {
    if (n == nullptr) {
        return;
    }

    // get the weight of the left subtree which is also the index of the root
    size_t leftWeight = n->left == nullptr ? 0 : n->left->weight;

    if (index < leftWeight) {
        // the item is in the left subtree
        removeRecursively(n->left, index);
        // update the weight of the current node, since the left subtree has item needs to be removed
        n->removeOne();
    } else if (index > leftWeight) {
        // the item is in the right subtree
        removeRecursively(n->right, index - leftWeight - 1);
        // update the weight of the current node, since the right subtree has item needs to be removed
        n->removeOne();
    } else {
        // the item is the root
        if (n->left == nullptr && n->right == nullptr) {
            // if the node is a leaf node, delete it
            delete n;
            n = nullptr;
        } else if (n->left == nullptr) {
            // if the node has only right child, replace the node with the right child
            Node *temp = n;
            n = n->right;
            delete temp;
        } else if (n->right == nullptr) {
            // if the node has only left child, replace the node with the left child
            Node *temp = n;
            n = n->left;
            delete temp;
        } else {
            // if the node has both left and right child
            // find the node n that contains the item at the next greater index
            Node *temp = n->right;
            while (temp->left != nullptr) {  // find the leftmost node of the right subtree
                temp->removeOne();
                temp = temp->left;
            }
            // swap the values of the two nodes
            n->data = temp->data;
            n->removeOne();
            // remove node n
            removeRecursively(n->right, index + 1);
        }
    }
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