#include "Counter.h"

// Counter Member Functions
Counter::Counter() {
    // The constructor should initialize any member variables.
    list = new List();
    index = new Index(10);
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
    // del(k) removes a key from the counter, setting its count to (implicit) zero.

    // if (list->find(key))
    //     std::cout << "found: " << key << " in the list" << '\n';

    // if (index->find(key))
    //     std::cout << "found: " << key << " in the index" << '\n';

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
    index->set_i(key, count, list);
}

void Counter::print() const {
    // bebug print function
    index->debugPrint();
}

void Counter::listkeys() const {
    // print all nodes in the list
    int i = 0;
    List::Node* current = list->head;
    while (current != nullptr) {
        std::cout << "Current key: "<< current->key << '\n';
        current = current->next;
        i++;
    }
    std::cout << "Total keys: " << i << '\n';
}

Counter::Iterator Counter::begin() const {
    // The begin() function should return an iterator to the first-inserted item in the counter.
    return Iterator(list->head);
}

Counter::Iterator Counter::end() const {
    // The end() function should return an iterator to the "end" of the counter.
    return Iterator(nullptr);
}