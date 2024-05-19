#include "Index.h"

#include <functional>
#include <iostream>

// Index Member Functions
Index::Index(int capacity) : count(0), capacity(capacity) {
    table = new Bucket[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = Bucket();
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
    for (int i = 0; i < capacity; i++) {
        if (table[i].node != nullptr) {
            total += table[i].node->value;
        }
    }
    return total;
}

int Index::hashFunction(const std::string& key) const {
    return std::hash<std::string>{}(key) % capacity;
}

void Index::insert_i(const std::string& key, int value, List* list) {
    if (count == capacity) {
        resizeAndRehash();
    }

    int index = hashFunction(key);
    while (table[index].node != nullptr && table[index].node->key != key) {
        index = (index + 1) % capacity;
    }

    if (table[index].node == nullptr) {
        count++;
        table[index].node = list->insert(key, value);
        table[index].isDirty = false;
    } else {
        table[index].node->value += value;
    }
}

List::Node* Index::find(const std::string& key) const {
    int index = hashFunction(key);
    int startIndex = index;

    while (table[index].node != nullptr || table[index].isDirty) {
        if (table[index].node != nullptr && table[index].node->key == key) {
            return table[index].node;
        }
        index = (index + 1) % capacity;
        if (index == startIndex) {  // Full loop, key not found
            return nullptr;
        }
    }

    return nullptr;
}

List::Node* Index::remove_i(const std::string& key, List* list) {
    int index = hashFunction(key);
    int startIndex = index;

    while (table[index].node != nullptr || table[index].isDirty) {
        if (table[index].node != nullptr && table[index].node->key == key) {
            List::Node* node = table[index].node;
            list->remove(node);
            table[index].node = nullptr;
            table[index].isDirty = true;
            return node;
        }
        index = (index + 1) % capacity;
        if (index == startIndex) {  // Full loop, key not found
            return nullptr;
        }
    }

    return nullptr;
}

void Index::remove(int index, List* list) {
    // remove the node at given index
    if (table[index].node != nullptr) {
        List::Node* node = table[index].node;
        list->remove(node);
        table[index].node = nullptr;
        count--;
    }
}

void Index::resizeAndRehash() {
    int oldCapacity = capacity;
    Bucket* oldTable = table;

    capacity = (count + 1) * 2;
    table = new Bucket[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = Bucket();
    }

    for (int i = 0; i < oldCapacity; i++) {
        if (oldTable[i].node != nullptr) {
            int index = hashFunction(oldTable[i].node->key);
            while (table[index].node != nullptr) {
                index = (index + 1) % capacity;
            }
            table[index].node = oldTable[i].node;
        }
    }

    delete[] oldTable;
}

// function to print every node in the table
void Index::debugPrint() const {
    for (int i = 0; i < capacity; i++) {
        if (table[i].node != nullptr) {
            std::cout << "Index: " << i << ", Key: " << table[i].node->key << ", Value: " << table[i].node->value << std::endl;
        }
    }
}
