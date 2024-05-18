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
int Index::getCount(){
    return count;
}

int Index::getTotal(){
    int total = 0;
    for (int i = 0; i < capacity; i++) {
        if (table[i] != nullptr) {
            total += table[i]->value;
        }
    }
    return total;
}

void Index::insert_index(const std::string& key, int value, List* list) {
    if (count == capacity) {
        resizeAndRehash();
    }

    // Insert the key into the table
    int index = hashFunction1(key);
    if (table[index] != nullptr && table[index]->key != key) {  // If collision
        int step = hashFunction2(key);
        do {
            index = (index + step) % capacity;
        } while (table[index] != nullptr && table[index]->key != key);
    }

    // If the index is empty, increment the count
    if (table[index] == nullptr) {
        count++;
    }
    table[index] = list->insert(key, value);  // list insert will insert and return the new node
}


void Index::insert_i(const std::string& key, int value, List* list) {
    if (count == capacity) {
        resizeAndRehash();
    }

    // Insert the key into the table
    int index = hashFunction1(key);
    if (table[index] != nullptr && table[index]->key != key) {  // If collision
        int step = hashFunction2(key);
        do {
            index = (index + step) % capacity;
        } while (table[index] != nullptr && table[index]->key != key);
    }

    // If the index is empty, increment the count and insert the key
    if (table[index] == nullptr) {
        count++;
        table[index] = list->insert(key, value);
    }else{
        // If the index is not empty, increment the value
        table[index]->value += value;
    }
}

List::Node* Index::find(const std::string& key) const {
    int index = hashFunction1(key);
    int startIndex = index; // Remember the start index

    if (table[index] == nullptr || table[index]->key == key) {
        return table[index];
    } else {
        int step = hashFunction2(key);
        do {
            index = (index + step) % capacity;
            if (index == startIndex) { // If we've checked all slots
                break; // Break the loop
            }
        } while (table[index] != nullptr && table[index]->key != key);

        return table[index];
    }
}

List::Node* Index::remove_index(const std::string& key, List* list) {
    int index = hashFunction1(key);
    if (table[index] == nullptr) {
        return nullptr;
    } else if (table[index]->key == key) {
        List::Node* node = table[index];
        table[index] = nullptr;
        count--;
        return node;
    } else {
        int step = hashFunction2(key);
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

void Index::remove_i(const std::string& key, List* list) {
    int index = hashFunction1(key);
    if (table[index] == nullptr) {
        // If the key is not found, do nothing
        return;
    } else if (table[index]->key == key) { // If the key is found
        List::Node* node = table[index];
        table[index] = nullptr;
        count--;
        list->remove(node);
    } else {
        // If the key is not found, search for it
        int step = hashFunction2(key);
        do {
            index = (index + step) % capacity;
        } while (table[index] != nullptr && table[index]->key != key);
        if (table[index] == nullptr) {
            return;
        } else {
            List::Node* node = table[index];
            table[index] = nullptr;
            count--;
            list->remove(node);
        }
    }
}

// Helper Functions
int Index::hashFunction1(const std::string& key) const {
    // Make sure the index is within the bounds of the array
    return std::hash<std::string>{}(key) % capacity;
}

int Index::hashFunction2(const std::string& key) const {
    // Make sure the step size is a positive number less than the capacity
    return 1 + (std::hash<std::string>{}(key) % (capacity - 1));
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
            int index = hashFunction1(oldTable[i]->key);
            if (table[index] != nullptr) {  // If collision
                int step = hashFunction2(oldTable[i]->key);
                do {
                    index = (index + step) % capacity;
                } while (table[index] != nullptr);
            }
            table[index] = oldTable[i];
        }
    }

    delete[] oldTable;
}
