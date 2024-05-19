#include "Index.h"

#include <functional>
#include <iostream>

// Dirty node
List::Node* const DIRTY = reinterpret_cast<List::Node*>(1);  // c++ style of (List::Node*) 1

// Index Member Functions
Index::Index(int capacity) : count(0), capacity(capacity) {
    table = new List::Node*[capacity];
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
    for (int i = 0; i < capacity; i++) {
        if (table[i] != nullptr && table[i] != DIRTY) {
            total += table[i]->value;
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
    int firstDirtyIndex = -1;
    while (table[index] != nullptr && table[index]->key != key) {
        if (firstDirtyIndex == -1 && table[index] == DIRTY) {
            firstDirtyIndex = index;
        }
        index = (index + 1) % capacity;
    }

    if (table[index] == nullptr) {
        count++;
        if (firstDirtyIndex != -1) {
            index = firstDirtyIndex;  // Fill in the first DIRTY slot we found
        }
        table[index] = list->insert(key, value);
    } else if (table[index]->key == key) {
        table[index]->value += value;
    }
}



List::Node* Index::find(const std::string& key) const {
    int index = hashFunction(key);
    int startIndex = index;
    // std::cout << "finding key " << key << "out side while" << std::endl;
    while (table[index] == nullptr || table[index] == DIRTY || table[index]->key != key) {
        // std::cout << "finding key " << key << " at index " << index << std::endl;
        index = (index + 1) % capacity;
        if (index == startIndex) {  // Full loop, key not found
            return nullptr;
        }
    }

    return table[index];
}

List::Node* Index::remove_i(const std::string& key, List* list) {
    int index = hashFunction(key);
    int startIndex = index;

    while (table[index] == nullptr || table[index] == DIRTY || table[index]->key != key) {
        index = (index + 1) % capacity;
        if (index == startIndex) {  // Full loop, key not found
            return nullptr;
        }
    }

    List::Node* node = table[index];
    table[index] = DIRTY;
    count--;
    if (node != DIRTY) {
        list->remove(node);
    }
    return node;
}

void Index::remove(int index, List* list) {
    // remove the node at given index
    if (table[index] != nullptr) {
        List::Node* node = table[index];
        list->remove(node);
        table[index] = nullptr;
        count--;
    }
}

void Index::resizeAndRehash() {
    int oldCapacity = capacity;
    List::Node** oldTable = table;

    capacity = (count + 1) * 2;
    table = new List::Node*[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }

    for (int i = 0; i < oldCapacity; i++) {
        if (oldTable[i] != nullptr && oldTable[i] != DIRTY) {
            int index = hashFunction(oldTable[i]->key);
            while (table[index] != nullptr) {
                index = (index + 1) % capacity;
            }
            table[index] = oldTable[i];
        }
    }

    delete[] oldTable;
}

// function to print every node in the table
void Index::debugPrint() const {
    for (int i = 0; i < capacity; i++) {
        if (table[i] == nullptr) {
            // Handle null nodes
        } else if (table[i] == DIRTY) {
            // Handle dirty nodes
        } else {
            std::cout << "Index: " << i << ", Key: " << table[i]->key << ", Value: " << table[i]->value << std::endl;
        }
    }
}