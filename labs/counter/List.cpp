// List.cpp

#include "List.h"

// Constructor
List::List() : head(nullptr), tail(nullptr), size(0) {}

// Destructor
List::~List() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

// Find a node by key
List::Node* List::find(const std::string& key) const {
    Node* current = head;
    while (current) {
        if (current->key == key) return current;
        current = current->next;
    }
    return nullptr;
}

// Push a new node
List::Node* List::push(const std::string& key, int value) {
    Node* newNode = new Node(key, value, nullptr, tail);
    if (!head) head = newNode;
    if (tail) tail->next = newNode;
    tail = newNode;
    ++size;
    return newNode;
}

// Remove a node
void List::remove(Node* node) {
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;
    if (node == head) head = node->next;
    if (node == tail) tail = node->prev;
    delete node;
    --size;
}

// Get the total of all node values
int List::getTotal() const {
    int total = 0;
    Node* current = head;
    while (current) {
        total += current->value;
        current = current->next;
    }
    return total;
}

// Get the size of the list
size_t List::getSize() const {
    return size;
}
