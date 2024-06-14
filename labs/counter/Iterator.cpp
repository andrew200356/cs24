#include "Counter.h"
// Constructor
Counter::Iterator::Iterator(List::Node* current) {
    this->current = current;
}

// Counter::Iterator Member Functions
const std::string& Counter::Iterator::key() const {
    return current->key;
}

int Counter::Iterator::value() const {
    return current->value;
}

void Counter::Iterator::operator++() {
    // The operator++() function should advance the iterator to the next item.
    current = current->next;
}

bool Counter::Iterator::operator==(const Iterator& other) const {
    // The operator==() function should compare two iterators for equality.
    if (current == nullptr || other.current == nullptr) {
        return current == other.current;
    }
    return current->key == other.current->key;
}

bool Counter::Iterator::operator!=(const Iterator& other) const {
    // The operator!=() function should compare two iterators for inequality.
    return !(*this == other);
}
