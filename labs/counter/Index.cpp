// Index.cpp

#include "Index.h"

#include <cstdint>
#include <cstring>
#include <iostream>

// Define the sentinel value for dirty nodes
List::Node* const Index::DIRTY = reinterpret_cast<List::Node*>(1);

#include <string>

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
    table = new List::Node*[capacity]();  // Initialize the array of List::Node pointers

    // initiailize the table with nullptr
    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
}

Index::~Index() {
    delete[] table;
}

int Index::getCount() {
    return count;
}

int Index::getTotal() {
    int total = 0;
    for (size_t i = 0; i < capacity; i++) {
        if (table[i] != nullptr && table[i] != DIRTY) {
            total += table[i]->value;
        }
    }
    return total;
}

List::Node* Index::find(const std::string& key) const {
    int index = hashFunction(key) % capacity;
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

void Index::insert_i(const std::string& key, int value, List* list) {
    if (static_cast<double>(count) / capacity > 0.7) {  // Resize and rehash if load factor > 0.7
        resizeAndRehash();
    }

    size_t index = hashFunction(key) % capacity;
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
    // std::cout << "right after resize" << std::endl;
    int index = hashFunction(key) % capacity;
    // std::cout << "lol\n";
    int i = 1;

    while (table[index] != nullptr && table[index] != DIRTY && table[index]->key != key) {
        // std::cout << "inside the while loop \n";
        index = (index + i * i) % capacity;
        i++;
    }

    // std::cout << "after the while loop \n";
    if (table[index] == nullptr || table[index] == DIRTY) {
        count++;
        table[index] = list->insert(key, value);
    } else {
        table[index]->value = value;
    }
}

void Index::remove_i(const std::string& key, List* list) {
    int index = hashFunction(key) % capacity;
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
    // std::cout << "resized\n";
    size_t oldCapacity = capacity;
    List::Node** oldTable = table;

    capacity = (count + 1) * 2;
    table = new List::Node*[capacity];

    // initiailize the table with nullptr
    for (size_t i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }

    for (size_t i = 0; i < oldCapacity; i++) {
        if (oldTable[i] != nullptr && oldTable[i] != DIRTY) {
            size_t index = hashFunction(oldTable[i]->key) % capacity;
            size_t j = 1;
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
    for (size_t i = 0; i < capacity; i++) {
        if (table[i] != nullptr && table[i] != DIRTY) {
            std::cout << "Index: " << i << ", Key: " << table[i]->key << ", Value: " << table[i]->value << std::endl;
        }
    }
}
