#include "Counter.h"

// Counter Member Functions
Counter::Counter() : mtotal(0) {
    // The constructor should initialize any member variables.
    list = new List();
    index = new Index();
}

Counter::~Counter() {
    // The destructor should free all memory allocated by the Counter.
    delete list;
    delete index;
}

size_t Counter::count() const {
    // The count() function should return the number of keys stored in the counter.
    return list->getSize();
}

int Counter::total() const {
    // total() returns the sum of all counts in the counter.
    return mtotal;
}

void Counter::inc(const std::string& key, int by) {
    List::Node* node = index->find(key);
    if (node) {
        node->value += by;
    } else {
        node = list->push(key, by);
        index->push(key, node);
    }
    mtotal += by;
}

void Counter::dec(const std::string& key, int by) {
    List::Node* node = index->find(key);
    if (node) {
        node->value -= by;
    } else {
        node = list->push(key, -by);
        index->push(key, node);
    }
    mtotal -= by;
}

void Counter::del(const std::string& key) {
    List::Node* node = index->find(key);
    if (node) {
        mtotal -= node->value;
        index->remove(key);
        list->remove(node);
    }
}

int Counter::get(const std::string& key) const {
    List::Node* keynode = index->find(key);
    return keynode == nullptr ? 0 : keynode->value;
}

void Counter::set(const std::string& key, int count) {
    List::Node* node = index->find(key);
    if (node) {
        mtotal += count - node->value;
        node->value = count;
    } else {
        node = list->push(key, count);
        index->push(key, node);
        mtotal += count;
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