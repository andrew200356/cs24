#include <iostream>

#include "Tree.h"

// This file is for you to test your tree functions.
// It won't be graded - do whatever you want.

void makeTree(Tree& tree) {
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

void testRemove(Tree& tree) {
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

    try {
        // Test 5: Try to remove a node that doesn't exist
        makeTree(tree);
        tree.remove(10);  // try to remove "z" (doesn't exist)
        std::cout << "After trying to remove a node that doesn't exist (z): " << std::endl;
        tree.print();
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    try {
        // Test 6: Try to remove from an empty tree
        Tree emptyTree;
        emptyTree.remove(0);  // try to remove from an empty tree
        std::cout << "After trying to remove from an empty tree: " << std::endl;
        emptyTree.print();
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
}

void testRotate() {
    // Test 1: Insert nodes in ascending order
    {
        Tree tree;
        for (char c = 'a'; c <= 'h'; ++c) {
            tree.insert(std::string(1, c));
        }
        std::cout << "After inserting nodes in ascending order: " << std::endl;
        tree.print();
    }

    // Test 2: Insert nodes in descending order
    {
        Tree tree;
        for (char c = 'h'; c >= 'a'; --c) {
            tree.insert(std::string(1, c));
        }
        std::cout << "After inserting nodes in descending order: " << std::endl;
        tree.print();
    }

    // Test 3: Insert nodes in a way that requires both left and right rotations
    {
        Tree tree;
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
        std::cout << "After inserting nodes in a way that requires both left and right rotations: " << std::endl;
        tree.print();
    }
}
int main() {

    // Create a tree
    Tree tree;
    testRemove(tree);

    return 0;
}