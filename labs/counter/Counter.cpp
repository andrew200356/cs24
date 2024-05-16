#include "Counter.h"

// Counter Member Functions
Counter::Counter() {
    // The default constructor creates an empty Counter.
}

Counter::~Counter() {
    // The destructor should free all memory allocated by the Counter.

    // delete list;
    delete list;
    // delete index;
}

Counter::Iterator Counter::begin() const {
    // The begin() function should return an iterator to the first-inserted item in the counter.
    return Iterator();
}

size_t Counter::count() const {
    // The count() function should return the number of keys stored in the counter.
    return list->getSize();
}

void Counter::inc(const std::string& key, int by) {
    // inc(k, d) increments a count by a given value (default one).

    // first find the key
    List::Node* keynode = list->find(key);  // Declare the Node class

    // if key is not found, add it to the list
    if (keynode == nullptr) {
        list->insert(key, by);
    } else {
        // if key is found, increment the value by by
        keynode->value += by;
    }
}

void Counter::dec(const std::string& key, int by) {
    // dec(k, d) decrements a count by a given value (default one).

    // same as inc, but decrement
    List::Node* keynode = list->find(key);

    if (keynode == nullptr) {
        list->insert(key, -by);
    } else {
        keynode->value -= by;
    }
}

void Counter::del(const std::string& key) {
    // del(k) removes a key from the counter, setting its count to (implicit) zero.
    List::Node* removed = list->remove(key);
    removed->value = 0;
    delete removed;
}

Counter::Iterator Counter::end() const {
    // The end() function should return an iterator to the "end" of the counter.
    return Iterator();
}

int Counter::get(const std::string& key) const {
    // get(k) looks up a count by key. If the key isn't present, it returns zero.
    List::Node* keynode = list->find(key);

    return keynode == nullptr ? 0 : keynode->value;
}

void Counter::set(const std::string& key, int count) {
    // set(k, v) sets a count by key.
    List::Node* keynode = list->find(key);
    keynode->value = count;
}

int Counter::total() const {
    // total() returns the sum of all counts in the counter.
    return list->getTotal();
}

// The inc(), dec(), and set() functions will add keys to the counter if they are not already present.
// The del() function is the only function that removes keys; setting a value to zero does not remove the corresponding key.