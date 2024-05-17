#include "Index.h"

// Index Member Functions
Index::Index(int capacity) : count(0), capacity(capacity) {
    table = new List::Node*[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }
}

Index::~Index() {
    // Just delete the table, the List destructor will take care of the nodes
    delete[] table;
}

// Member Functions

size_t Index::hashFunction1(const std::string& key) const {
    std::hash<std::string> hasher;
    size_t hash = hasher(key);
    return hash % capacity;
}

size_t Index::hashFunction2(const std::string& key) const {
    std::hash<std::string> hasher;
    size_t hash = hasher(key);
    return (capacity - 1) - (hash % (capacity - 1));
}

void Index::resizeAndRehash() {
    int oldCapacity = capacity;
    List::Node** oldTable = table;

    // Double the capacity
    capacity = (count + 1) * 2;
    table = new List::Node*[capacity];
    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;
    }

    // Rehash all keys from the old table into the new one
    for (int i = 0; i < oldCapacity; i++) {
        if (oldTable[i] != nullptr) {
            size_t index = hashFunction1(oldTable[i]->key);
            if (table[index] != nullptr) {  // If collision
                size_t step = hashFunction2(oldTable[i]->key);
                do {
                    index = (index + step) % capacity;
                } while (table[index] != nullptr);
            }
            table[index] = oldTable[i];
        }
    }

    delete[] oldTable;
}

void Index::insert_index(const std::string& key, int value, List* list) {
    if (count == capacity) {
        resizeAndRehash();
    }

    size_t index = hashFunction1(key);
    if (table[index] != nullptr && table[index]->key != key) {  // If collision
        size_t step = hashFunction2(key);
        do {
            index = (index + step) % capacity;
        } while (table[index] != nullptr && table[index]->key != key);
    }

    if (table[index] == nullptr) {
        count++;
    }
    table[index] = list->insert(key, value);  // list insert will insert and return the new node
}

List::Node* Index::find(const std::string& key) const {
    size_t index = hashFunction1(key);
    if (table[index] == nullptr || table[index]->key == key) {
        return table[index];
    } else {
        size_t step = hashFunction2(key);
        do {
            index = (index + step) % capacity;
        } while (table[index] != nullptr && table[index]->key != key);
        return table[index];
    }
}

List::Node* Index::remove_index(const std::string& key, List* list) {
    size_t index = hashFunction1(key);
    if (table[index] == nullptr) {
        return nullptr;
    } else if (table[index]->key == key) {
        List::Node* node = table[index];
        table[index] = nullptr;
        count--;
        return node;
    } else {
        size_t step = hashFunction2(key);
        do {
            index = (index + step) % capacity;
        } while (table[index] != nullptr && table[index]->key != key);
        if (table[index] == nullptr) {
            return nullptr;
        } else {
            List::Node* node = table[index];
            table[index] = nullptr;
            count--;
            return node;
        }
    }
}