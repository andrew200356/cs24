#include "Counter.h"

// Counter Member Functions
Counter::Counter() {
    // The constructor should initialize any member variables.
    list = new List();
    index = new Index(50);
}

Counter::~Counter() {
    // The destructor should free all memory allocated by the Counter.
    delete list;
    delete index;
}

size_t Counter::count() const {
    // The count() function should return the number of keys stored in the counter.
    return index->getCount();
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
    // del(k) removes a key from the counter, setting its count to (implicit) zero.
    index->remove_i(key, list);
}

int Counter::get(const std::string& key) const {
    // get(k) looks up a count by key. If the key isn't present, it returns zero.

    // std::cout << "counter getter trying to get: " << key << '\n';

    List::Node* keynode = index->find(key);

    // if (keynode == nullptr)
    // {
    //     std::cout << "counter getter not found: " << key << '\n';
    // }else{
    //     std::cout << "counter getter found: " << keynode->key << '\n';
    // }
    return keynode == nullptr ? 0 : keynode->value;
}

void Counter::set(const std::string& key, int count) {
    // set(k, v) sets a count by key.
    List::Node* keynode = index->find(key);
    if (keynode == nullptr) {
        index->insert_index(key, count, list);
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