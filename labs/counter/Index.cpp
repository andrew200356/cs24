#include "Index.h"

#include <functional>
#include <iostream>

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
        if (table[i] != nullptr) {
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
    while (table[index] != nullptr && table[index]->key != key) {
        index = (index + 1) % capacity;
    }

    if (table[index] == nullptr) {
        count++;
        table[index] = list->insert(key, value);
    } else {
        table[index]->value += value;
    }
}

List::Node* Index::find(const std::string& key) const {
    int index = hashFunction(key);
    int startIndex = index;
    // std::cout << "finding key " << key << "out side while" << std::endl;
    //  if the index is not null and the key is not the same as the key we are looking for
     while (table[index] != nullptr && table[index]->key != key) {
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

    while (table[index] != nullptr && table[index]->key != key) {
        // std::cout << "finding key " << key << " at index " << index << std::endl;
        index = (index + 1) % capacity;
        if (index == startIndex) {  // Full loop, key not found
            return nullptr;
        }
    }

    if (table[index] == nullptr) {
        return nullptr;
    } else {
        List::Node* node = table[index];
        table[index] = nullptr;
        count--;
        list->remove(node);
        return node;
    }
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
        if (oldTable[i] != nullptr) {
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
        if (table[i] != nullptr) {
            std::cout << "Index: " << i << ", Key: " << table[i]->key << ", Value: " << table[i]->value << std::endl;
        }
    }
}
