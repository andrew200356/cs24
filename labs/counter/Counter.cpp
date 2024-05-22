#include "Counter.h"

// Counter Member Functions
Counter::Counter() {
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
    return index->getTotal();
}

void Counter::inc(const std::string& key, int by) {
    index->insert_i(key, by, list);
}

void Counter::dec(const std::string& key, int by) {
    index->insert_i(key, -by, list);
}

void Counter::del(const std::string& key) {
    index->remove_i(key, list);
}

int Counter::get(const std::string& key) const {
    List::Node* keynode = index->find(key);
    return keynode == nullptr ? 0 : keynode->value;
}

void Counter::set(const std::string& key, int count) {
    // set(k, v) sets a count by key.
    index->set_i(key, count, list);
}

void Counter::print() const {
    // bebug print function
    index->debugPrint();
}

Counter::Iterator Counter::begin() const {
    // The begin() function should return an iterator to the first-inserted item in the counter.
    return Iterator(list->head);
}

Counter::Iterator Counter::end() const {
    // The end() function should return an iterator to the "end" of the counter.
    return Iterator(nullptr);
}