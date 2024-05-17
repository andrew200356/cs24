#include "List.h"

#include <iostream>

// List Member Functions

// Constructor
List::List() {
    head = nullptr;
    tail = nullptr;
    size = 0;
}

// Destructor
List::~List() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

// Helper Functions
List::Node* List::find(const std::string& key) const {
    // std::cout << "trying to find " << key << '\n';
    Node* current = head;
    while (current != nullptr) {
        if (current->key == key) {
            // std::cout << "Found " << key << '\n';
            return current;
        }
        current = current->next;
    }
    // std::cout << "Not Found " << key << '\n';
    return nullptr;
}

// Member Functions
List::Node* List::insert(const std::string& key, int value) {
    // insert a new node with the given key and value, and return the new node

    // Create a new node and insert it at the tail
    Node* newNode = new Node(key, value, nullptr, tail);

    // std::cout << "Inserting " << key << " with value " << value << '\n';

    // Update the head
    if (head == nullptr) {
        head = newNode;
    }

    // Update the tail
    if (tail != nullptr) {
        // Update the next pointer of the previous tail
        tail->next = newNode;
    }
    tail = newNode;

    size++;
    return newNode;
}

List::Node* List::remove(List::Node* node) {
    // remove the given node from the list and return it

    if (node->prev != nullptr) {
        node->prev->next = node->next;
    } else {
        head = node->next;
    }

    if (node->next != nullptr) {
        node->next->prev = node->prev;
    } else {
        tail = node->prev;
    }

    size--;
    return node;
}

int List::getTotal() {
    int total = 0;
    Node* current = head;
    while (current != nullptr) {
        total += current->value;
        current = current->next;
    }
    return total;
}