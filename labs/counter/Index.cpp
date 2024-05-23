// Index.cpp

#include "Index.h"

#include <cstdint>

List::Node* const Index::DIRTY = reinterpret_cast<List::Node*>(1);

constexpr uint32_t FNV_32_OFFSET_BASIS = 0x811c9dc5;
constexpr uint32_t FNV_32_PRIME = 0x01000193;

int Index::hashFunction(const std::string& key) const {
    uint32_t hash = FNV_32_OFFSET_BASIS;
    for (char c : key) {
        hash ^= static_cast<uint32_t>(c);
        hash *= FNV_32_PRIME;
    }
    return static_cast<int>(hash);
}

Index::Index(int capacity) : count(0), capacity(capacity) {
    table = new List::Node*[capacity]();
}

Index::~Index() {
    delete[] table;
}

List::Node* Index::find(const std::string& key) const {
    if (wanted != nullptr && wanted->key == key) {
        return wanted;
    }

    size_t index = hashFunction(key) % capacity;
    size_t i = 1;

    while (table[index]) {
        if (table[index] != DIRTY && table[index]->key == key) {
            wanted = table[index];
            return wanted;
        }
        index = (index + i * i) % capacity;
        ++i;
    }

    return nullptr;
}

void Index::push(const std::string& key, List::Node* node) {
    if (static_cast<double>(count) / capacity > 0.7) {
        resizeAndRehash();
    }

    size_t index = hashFunction(key) % capacity;
    size_t i = 1;

    while (table[index] && table[index] != DIRTY && table[index]->key != key) {
        index = (index + i * i) % capacity;
        ++i;
    }

    if (!table[index] || table[index] == DIRTY) {
        ++count;
        table[index] = node;
    } else {
        table[index]->value = node->value;
    }
}

void Index::remove(const std::string& key) {
    size_t index = hashFunction(key) % capacity;
    size_t i = 1;

    while (table[index]) {
        if (table[index] != DIRTY && table[index]->key == key) {
            table[index] = DIRTY;
            wanted = nullptr;
            --count;
            return;
        }
        index = (index + i * i) % capacity;
        ++i;
    }
}

void Index::resizeAndRehash() {
    size_t oldCapacity = capacity;
    List::Node** oldTable = table;

    capacity = count * 2;
    table = new List::Node*[capacity]();

    for (size_t i = 0; i < oldCapacity; ++i) {
        if (oldTable[i] && oldTable[i] != DIRTY) {
            size_t index = hashFunction(oldTable[i]->key) % capacity;
            size_t j = 1;
            while (table[index]) {
                index = (index + j * j) % capacity;
                ++j;
            }
            table[index] = oldTable[i];
        }
    }

    delete[] oldTable;
}
