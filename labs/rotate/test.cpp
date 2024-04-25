#include <iostream>

#include "Tree.h"

// This file is for you to test your tree functions.
// It won't be graded - do whatever you want.

int main() {
    // Do tree things!
    // create a tree
    Tree tree;
    // insert some values
    tree.insert("a");
    tree.insert("b");
    tree.insert("c");
    tree.insert("d");
    tree.insert("e");

    // print the tree
    tree.print();

    // find the index of a value
    std::cout << "Find index of 'c': " << tree.find("c") << std::endl;
    std::cout << "Find index of 'e': " << tree.find("e") << std::endl;
    std::cout << "Find index of 'x': " << tree.find("x") << std::endl;

    // find the value at index
    std::cout << "Look up for index 2: " << tree.lookup(2) << std::endl;
    std::cout << "Look up for index 4: " << tree.lookup(4) << std::endl;
    std::cout << "Look up for index 5: " << tree.lookup(5) << std::endl;

    // test contains
    std::string containsB = tree.contains("b") ? "ture" : "false";
    std::string containsX = tree.contains("x") ? "ture" : "false";
    std::cout << "Contains 'b': " << containsB << std::endl;
    std::cout << "Contains 'x': " << containsX << std::endl;

    return 0;
}
