// Index.cpp

#include "Index.h"
#include <cstdint>
#include <cstring>
#include <iostream>

// Define the sentinel value for dirty nodes
List::Node* const Index::DIRTY = reinterpret_cast<List::Node*>(1);

// MurmurHash3 implementation
uint32_t MurmurHash3(const char* key, uint32_t len, uint32_t seed = 42) {
    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;
    const uint32_t r1 = 15;
    const uint32_t r2 = 13;
    const uint32_t m = 5;
    const uint32_t n = 0xe6546b64;

    uint32_t hash = seed;

    const int nblocks = len / 4;
    const uint32_t* blocks = (const uint32_t*)(key);
    for (int i = 0; i < nblocks; i++) {
        uint32_t k = blocks[i];
        k *= c1;
        k = (k << r1) | (k >> (32 - r1));
        k *= c2;

        hash ^= k;
        hash = (hash << r2) | (hash >> (32 - r2));
        hash = hash * m + n;
    }

    const uint8_t* tail = (const uint8_t*)(key + nblocks * 4);
    uint32_t k1 = 0;
    switch (len & 3) {
        case 3:
            k1 ^= tail[2] << 16;
            [[fallthrough]];
        case 2:
            k1 ^= tail[1] << 8;
            [[fallthrough]];
        case 1:
            k1 ^= tail[0];
            k1 *= c1;
            k1 = (k1 << r1) | (k1 >> (32 - r1));
            k1 *= c2;
            hash ^= k1;
    }

    hash ^= len;
    hash ^= hash >> 16;
    hash *= 0x85ebca6b;
    hash ^= hash >> 13;
    hash *= 0xc2b2ae35;
    hash ^= hash >> 16;

    return hash;
}

int Index::hashFunction(const std::string& key) const {
    return MurmurHash3(key.c_str(), key.size()) % capacity;
}

Index::Index(int capacity) : count(0), capacity(capacity) {
    table = new List::Node*[capacity](); // Initialize the array of List::Node pointers
}

Index::~Index() {
    delete[] table;
}

int Index::getCount() {
    return count;
}

int Index::getTotal() {
    int total = 0;
    for (int i = 0; i < capacity; i++) {
        if (table[i] != nullptr && table[i] != DIRTY) {
            total += table[i]->value;
        }
    }
    return total;
}

void Index::insert_i(const std::string& key, int value, List* list) {
    if (static_cast<double>(count) / capacity > 0.7) {  // Resize and rehash if load factor > 0.7
        resizeAndRehash();
    }

    int index = hashFunction(key);
    int i = 1;

    while (table[index] != nullptr && table[index] != DIRTY && table[index]->key != key) {
        index = (index + i * i) % capacity;
        i++;
    }

    if (table[index] == nullptr || table[index] == DIRTY) {
        count++;
        table[index] = list->insert(key, value);
    } else {
        table[index]->value += value;
    }
}

void Index::set_i(const std::string& key, int value, List* list) {
    if (static_cast<double>(count) / capacity > 0.7) {  // Resize and rehash if load factor > 0.7
        resizeAndRehash();
    }

    int index = hashFunction(key);
    int i = 1;

    while (table[index] != nullptr && table[index] != DIRTY && table[index]->key != key) {
        index = (index + i * i) % capacity;
        i++;
    }

    if (table[index] == nullptr || table[index] == DIRTY) {
        count++;
        table[index] = list->insert(key, value);
    } else {
        table[index]->value = value;
    }
}

List::Node* Index::find(const std::string& key) const {
    int index = hashFunction(key);
    int i = 1;

    while (table[index] != nullptr) {
        if (table[index] != DIRTY && table[index]->key == key) {
            return table[index];
        }
        index = (index + i * i) % capacity;
        i++;
    }

    return nullptr;
}

void Index::remove_i(const std::string& key, List* list) {
    int index = hashFunction(key);
    int i = 1;

    while (table[index] != nullptr) {
        if (table[index] != DIRTY && table[index]->key == key) {
            list->remove(table[index]);
            table[index] = DIRTY;
            count--;
            return;
        }
        index = (index + i * i) % capacity;
        i++;
    }
}

void Index::resizeAndRehash() {
    int oldCapacity = capacity;
    List::Node** oldTable = table;

    capacity = (count + 1) * 2;
    table = new List::Node*[capacity]();

    for (int i = 0; i < oldCapacity; i++) {
        if (oldTable[i] != nullptr && oldTable[i] != DIRTY) {
            int index = hashFunction(oldTable[i]->key);
            int j = 1;
            while (table[index] != nullptr) {
                index = (index + j * j) % capacity;
                j++;
            }
            table[index] = oldTable[i];
        }
    }

    delete[] oldTable;
}

void Index::debugPrint() const {
    for (int i = 0; i < capacity; i++) {
        if (table[i] != nullptr && table[i] != DIRTY) {
            std::cout << "Index: " << i << ", Key: " << table[i]->key << ", Value: " << table[i]->value << std::endl;
        }
    }
}
