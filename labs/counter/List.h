#ifndef LIST_H
#define LIST_H

// Double Linked List that stores a key and a value
// (std::string, int) pairs
// The list should support insertion at the tail,
// finding the node that contains a given string,
// and removal of any node.
// this is the header file for the List class

#include <string>

class List {
   public:
    // Node class
    class Node {
       public:
        std::string key;
        int value;
        Node* next;
        Node* prev;

        // Constructor
        Node(const std::string& key, int value, Node* next, Node* prev)
            : key(key), value(value), next(next), prev(prev) {}
    };

    // Member Variables
    Node* head;
    Node* tail;

    // Constructor
    List();

    // Destructor
    ~List();

    // Member Functions
    Node* find(const std::string& key) const;
    Node* insert(const std::string& key, int value);
    void remove(Node* node);
    int getTotal();
};

#endif
