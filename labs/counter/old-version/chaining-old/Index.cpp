// Index.cpp

#include "Index.h"

#include <cstdint>
#include <cstring>
#include <iostream>

constexpr uint32_t FNV_32_OFFSET_BASIS = 0x811c9dc5;
constexpr uint32_t FNV_32_PRIME = 0x01000193;

int Index::hashFunction(const std::string& key) const {
    uint32_t hash = FNV_32_OFFSET_BASIS;
    for (char c : key) {
        hash ^= static_cast<uint32_t>(c);
        hash *= FNV_32_PRIME;
    }
    return static_cast<int>(hash % capacity);
}

Index::Index(int capacity) : count(0), capacity(capacity) {
    table = new Chain*[capacity]();
}

Index::~Index() {
    for (int i = 0; i < capacity; ++i) {
        Chain* current = table[i];
        while (current != nullptr) {
            Chain* next = current->next;
            delete current;
            current = next;
        }
    }
    delete[] table;
}

int Index::getCount() {
    return count;
}

int Index::getTotal() {
    int total = 0;
    for (int i = 0; i < capacity; ++i) {
        Chain* current = table[i];
        while (current != nullptr) {
            total += current->node->value;
            current = current->next;
        }
    }
    return total;
}

List::Node* Index::find(const std::string& key) const {
    // store the node in wanted and look for wanted first
    if (wanted != nullptr && wanted->key == key) {
        return wanted;
    }

    int index = hashFunction(key);
    Chain* current = table[index];

    while (current != nullptr) {
        if (current->node->key == key) {
            wanted = current->node;
            return current->node;
        }
        current = current->next;
    }

    return nullptr;
}

void Index::insert_i(const std::string& key, int value, List* list) {
    // store the node in wanted and look for wanted first
    if (wanted != nullptr && wanted->key == key) {
        wanted->value += value;
        return;
    }

    if (static_cast<double>(count) / capacity > 0.7) {  // Resize and rehash if load factor > 0.7
        resizeAndRehash();
    }

    int index = hashFunction(key);
    Chain* current = table[index];

    while (current != nullptr) {
        if (current->node->key == key) {
            current->node->value += value;
            wanted = current->node;
            return;
        }
        current = current->next;
    }

    List::Node* newNode = list->insert(key, value);
    table[index] = new Chain(newNode, table[index]);
    count++;
}

void Index::set_i(const std::string& key, int value, List* list) {
    if (wanted != nullptr && wanted->key == key) {
        wanted->value = value;
        return;
    }

    if (static_cast<double>(count) / capacity > 0.7) {  // Resize and rehash if load factor > 0.7
        resizeAndRehash();
    }

    int index = hashFunction(key);
    Chain* current = table[index];

    while (current != nullptr) {
        if (current->node->key == key) {
            current->node->value = value;
            wanted = current->node;
            return;
        }
        current = current->next;
    }

    List::Node* newNode = list->insert(key, value);
    table[index] = new Chain(newNode, table[index]);
    count++;
}

void Index::remove_i(const std::string& key, List* list) {
    int index = hashFunction(key);
    Chain* current = table[index];
    Chain* prev = nullptr;

    while (current != nullptr) {
        if (current->node->key == key) {
            if (prev == nullptr) {
                table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            list->remove(current->node);
            delete current;
            wanted = nullptr;
            count--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void Index::resizeAndRehash() {
    int oldCapacity = capacity;
    Chain** oldTable = table;

    capacity = count * 2;
    table = new Chain*[capacity]();

    for (int i = 0; i < oldCapacity; ++i) {
        Chain* current = oldTable[i];
        while (current != nullptr) {
            Chain* next = current->next;
            int index = hashFunction(current->node->key);
            current->next = table[index];
            table[index] = current;
            current = next;
        }
    }

    delete[] oldTable;
}
