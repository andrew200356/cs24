#include "List.h"

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
    Node* current = head;
    while (current != nullptr) {
        if (current->key == key) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

List::Node* List::begin() const {
    return head;
}

// Member Functions
void List::insert(const std::string& key, int value) {
    // Create a new node and insert it at the tail
    Node* newNode = new Node(key, value, nullptr, tail);
    if (tail != nullptr) {
        tail->next = newNode;
    } else {
        tail = newNode;
    }
}

List::Node* List::remove(const std::string& key) {
    // remove and return the node with the given key
    Node* node = find(key);
    if (node == nullptr) {
        return node;
    }

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

    return node;
}

size_t List::getSize() {
    return size;
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