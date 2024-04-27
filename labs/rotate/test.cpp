#include <iostream>

#include "Tree.h"

// This file is for you to test your tree functions.
// It won't be graded - do whatever you want.

void makeTree(Tree &tree) {
    tree.clear();
    // Insert some values
    tree.insert("f");
    tree.insert("d");
    tree.insert("j");
    tree.insert("b");
    tree.insert("e");
    tree.insert("g");
    tree.insert("k");
    tree.insert("a");
    tree.insert("c");
    tree.insert("i");
    tree.insert("h");
}

int main() {
    // Create a tree
    Tree tree;

    // Print the tree
    std::cout << "The tree after insert: " << std::endl;
    tree.print();

    // Test 1: Remove a leaf node
    makeTree(tree);
    tree.remove(0);  // remove "a"
    std::cout << "After removing a leaf node (a): " << std::endl;
    tree.print();

    // Test 2: Remove a node with one child
    makeTree(tree);
    tree.remove(1);  // remove "b"
    std::cout << "After removing a node with one child (b): " << std::endl;
    tree.print();

    // Test 3: Remove a node with two children
    makeTree(tree);
    tree.remove(3);  // remove "d"
    std::cout << "After removing a node with two children (d): " << std::endl;
    tree.print();

    // Test 4: Remove the root node
    makeTree(tree);
    tree.remove(5);  // remove "f"
    std::cout << "After removing the root node (f): " << std::endl;
    tree.print();

    // Test 5: Try to remove a node that doesn't exist
    makeTree(tree);
    tree.remove(10);  // try to remove "z" (doesn't exist)
    std::cout << "After trying to remove a node that doesn't exist (z): " << std::endl;
    tree.print();

    // Test 6: Try to remove from an empty tree
    Tree emptyTree;
    emptyTree.remove(0);  // try to remove from an empty tree
    std::cout << "After trying to remove from an empty tree: " << std::endl;
    emptyTree.print();

    return 0;
}