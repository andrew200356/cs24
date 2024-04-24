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
    return 0;
}
