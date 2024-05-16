#include "Counter.h"
// Constructor
Counter::Iterator::Iterator(List::Node* current) {
    // The constructor should initialize the Counter.
}

// Counter::Iterator Member Functions
const std::string& Counter::Iterator::key() const {
    // The key() function should return the key of the current item.
    return current->key;
}

int Counter::Iterator::value() const {
    // The value() function should return the value of the current item.
    return current->value;
}

void Counter::Iterator::operator++() {
    // The operator++() function should advance the iterator to the next item.
    current = current->next;
}

bool Counter::Iterator::operator==(const Iterator& other) const {
    // The operator==() function should compare two iterators for equality.
    if (current == nullptr && other.current == nullptr) {
        return true;
    } else if (current == nullptr || other.current == nullptr) {
        return false;
    }
    return current->key == other.current->key;
}

bool Counter::Iterator::operator!=(const Iterator& other) const {
    // The operator!=() function should compare two iterators for inequality.
    return !(*this == other);
}
