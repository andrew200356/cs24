#include "Index.h"

#include <cstdint>
#include <cstring>  // For memset

List::Node* const Index::DIRTY = reinterpret_cast<List::Node*>(1);

constexpr uint32_t FNV_32_OFFSET_BASIS = 0x811c9dc5;
constexpr uint32_t FNV_32_PRIME = 0x01000193;

// Primary hash function (FNV-1a)
int Index::hashFunction(const std::string& key) const {
    uint32_t hash = FNV_32_OFFSET_BASIS;
    for (char c : key) {
        hash ^= static_cast<uint32_t>(c);
        hash *= FNV_32_PRIME;
    }
    return static_cast<int>(hash);
}

// Helper function to get index in charTable
int Index::getCharIndex(char c) const {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    }
    return -1;
}

Index::Index(int capacity) : count(0), capacity(capacity) {
    table = new List::Node*[capacity]();
    charTable = new List::Node*[26]();
}

Index::~Index() {
    delete[] table;
    delete[] charTable;
}

List::Node* Index::find(const std::string& key) const {
    if (key.size() == 1) {
        char upperKey = std::toupper(key[0]);
        int charIndex = getCharIndex(upperKey);
        if (charIndex != -1) {
            return charTable[charIndex];
        }
    }

    size_t index = hashFunction(key) % capacity;
    size_t i = 0;

    while (table[index]) {
        if (table[index] != DIRTY && table[index]->key == key) {
            return table[index];
        }
        index = (index + i * i) % capacity;
        ++i;
    }

    return nullptr;
}

void Index::push(const std::string& key, List::Node* node) {
    if (key.size() == 1) {
        char upperKey = std::toupper(key[0]);
        int charIndex = getCharIndex(upperKey);
        if (charIndex != -1) {
            charTable[charIndex] = node;
            return;
        }
    }

    if (static_cast<double>(count) / capacity > 0.7) {
        resizeAndRehash();
    }

    size_t index = hashFunction(key) % capacity;
    size_t i = 0;

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
    if (key.size() == 1) {
        char upperKey = std::toupper(key[0]);
        int charIndex = getCharIndex(upperKey);
        if (charIndex != -1) {
            charTable[charIndex] = nullptr;
            return;
        }
    }

    size_t index = hashFunction(key) % capacity;
    size_t i = 0;

    while (table[index]) {
        if (table[index] != DIRTY && table[index]->key == key) {
            table[index] = DIRTY;
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

    capacity = (count + 1) * 2;
    table = new List::Node*[capacity]();

    for (size_t i = 0; i < oldCapacity; ++i) {
        if (oldTable[i] && oldTable[i] != DIRTY) {
            size_t index = hashFunction(oldTable[i]->key) % capacity;
            size_t j = 0;
            while (table[index]) {
                index = (index + j * j) % capacity;
                ++j;
            }
            table[index] = oldTable[i];
        }
    }

    delete[] oldTable;
}
