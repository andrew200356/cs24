#include "Counter.h"

// Counter Member Functions
Counter::Counter() {
    // The constructor should initialize any member variables.
    list = new List();
    index = Index();
}

Counter::~Counter() {
    // The destructor should free all memory allocated by the Counter.
    delete list;
}

size_t Counter::count() const {
    // The count() function should return the number of keys stored in the counter.
    return list->size;
}

int Counter::total() const {
    // total() returns the sum of all counts in the counter.
    return list->getTotal();
}

void Counter::inc(const std::string& key, int by) {
    List::Node* keynode = index.find(key);  // Declare the Node class

    // if key is not found, add it to the list
    if (keynode == nullptr) {
        index.insert_index(key, by, list);
        // std::cout << "Key not found, adding " << key << " with value " << by << '\n';
    } else {
        // if key is found, increment the value by by
        keynode->value += by;
        // std::cout << "Key found, incrementing " << key << " by " << by << '\n';
    }
}

void Counter::dec(const std::string& key, int by) {
    // dec(k, d) decrements a count by a given value (default one).

    // same as inc, but decrement
    List::Node* keynode = index.find(key);

    if (keynode == nullptr) {
        index.insert_index(key, -by, list);
    } else {
        keynode->value -= by;
    }
}

void Counter::del(const std::string& key) {
    // del(k) removes a key from the counter, setting its count to (implicit) zero.
    List::Node* removed = index.remove_index(key, list);
    removed->value = 0;
    delete removed;
}

int Counter::get(const std::string& key) const {
    // get(k) looks up a count by key. If the key isn't present, it returns zero.
    List::Node* keynode = index.find(key);

    return keynode == nullptr ? 0 : keynode->value;
}

void Counter::set(const std::string& key, int count) {
    // set(k, v) sets a count by key.
    List::Node* keynode = index.find(key);
    if (keynode == nullptr) {
        list->insert(key, count);
        return;
    }
    keynode->value = count;
}

void Counter::print() const {
    // bebug print function

    List::Node* node = list->head;

    while (node != nullptr) {
        std::cout << node->key << ": " << node->value << '\n';
        node = node->next;
    }
}

Counter::Iterator Counter::begin() const {
    // The begin() function should return an iterator to the first-inserted item in the counter.
    return Iterator(list->head);
}

Counter::Iterator Counter::end() const {
    // The end() function should return an iterator to the "end" of the counter.
    return Iterator(nullptr);
}