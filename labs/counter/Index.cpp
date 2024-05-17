#include "Index.h"

// Index Member Functions
Index::Index(int capacity) : count(0), capacity(capacity) {
    table = new List::Node*[capacity];
    for (int i = 0; i < capacity; ++i) {
        table[i] = nullptr;
    }
}

Index::~Index() {
    // Just delete the table, the List destructor will take care of the nodes
    delete[] table;
}

// Member Functions

size_t Index::hashFunction(const std::string& key) const {
    // The hashFunction() function should return the hash value of a key.
    // The hash value should be the sum of the ASCII values of the characters in the key modulo the capacity of the index.

    // size_t hash = 0;
    // for (char c : key) {
    //     hash += c;
    // }
    std::hash<std::string> hasher;
    size_t hash = hasher(key);
    return hash % capacity;
}

void Index::insert_index(const std::string& key, int value, List* list) {
    // The insert() function should insert a key-value pair into the index.
    // If the key is already in the index, the value should be updated.
    // If the key is not in the index, a new node should be created and inserted into the appropriate list.
    List::Node* keynode = find(key);

    if (keynode == nullptr) {
        // If the key is not in the index, create a new node and insert it into the list
        keynode = list->insert(key, value);  // list insert will insert and return the new node
        count++;
    } else {
        // If the key is in the index, add the new value to the next of the keynode
    }
}

List::Node* Index::find(const std::string& key) const {
    // The find() function should return the node with the given key from the index.
    // If the key is not in the index, the function should return nullptr.
    size_t index = hashFunction(key);
    return table[index];
}

List::Node* Index::remove_index(const std::string& key, List* list) {
    // The remove() function should remove the node with the given key from the index.
    // If the key is not in the index, the function should return nullptr.
    size_t index = hashFunction(key);
    List::Node* keynode = table[index];
    if (keynode == nullptr) {
        return nullptr;
    }
    list->remove(keynode);  // Call the remove function on the list instance
    // notice now that the keynode is removed from the list, it is not deleted

    // Update the table
    table[index] = nullptr;
    count--;
    return keynode;
}