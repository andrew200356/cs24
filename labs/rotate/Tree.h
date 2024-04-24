#ifndef TREE_H
#define TREE_H

#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "Node.h"

class Tree {
    // Member Variables
    Node *root;
    size_t weight = 0;
    // Private Helper Functions
    size_t height(Node *n) const;                                                // returns the height of the tree with Recursion
    bool isBalanced(Node *root);                                                 // returns whether the tree is balanced with Recursion
    void clearRecursively(Node *n);                                              // removes all items from the tree with Recursion
    void printInorder(Node *n) const;                                            // prints the tree in tree notation with Recursion
    void removeRecursively(Node *n, size_t index);                               // removes the item at a given index with Recursion
    size_t f_inorder(Node *n, const std::string &s, size_t &index) const;        // returns the index of an item with Recursion
    std::string nth_inorder(struct Node *n, size_t index, size_t wanted) const;  // returns the item at a given index with Recursion

   public:
    Tree();
    ~Tree();

    // Public Member Functions
    void clear();                               // removes all items from the tree
    size_t count() const;                       // reports the number of items in the tree.
    bool contains(const std::string &s) const;  // reports whether the tree contains the given string.
    size_t find(const std::string &s) const;    // returns the index of an item. If there are multiple copies of the item, it returns the smallest index. If the item is not present in the tree, it returns the maximum value that can be stored in a size_t.
    void insert(const std::string &s);          // adds an item to the tree as a leaf node. If that item is already present in the tree, you will encounter it on your way down to a leaf node; if this happens, insert the new item into the old item's left subtree.
    std::string lookup(size_t index) const;     // returns the item at a given index. If the index is invalid, it throws a std::out_of_range exception.
    void print() const;                         //  prints the tree in tree notation, as explained below, followed by a newline.
    void remove(size_t index);                  // removes the item at a given index. If the index is invalid, it throws a std::out_of_range exception.
    /*
    If the item to be removed is on a leaf node, simply remove it.
    If the item to be removed is on a node with one child, that child takes the node's place.
    If the item is on a node with two children, find the node n that contains the item at the next greater index. Swap the values of the two nodes and remove node n. Node n is guaranteed to have one or zero children.
    */
};

#endif
