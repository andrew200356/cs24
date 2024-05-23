#ifndef INDEX_H
#define INDEX_H

#include <cstddef>
#include <string>
#include "List.h"

class Index {
public:
    Index(int capacity = 86000);
    ~Index();
    
    void push(const std::string& key, List::Node* node);
    List::Node* find(const std::string& key) const;
    void remove(const std::string& key);

private:
    struct Entry {
        std::string key;
        List::Node* node;
        Entry* next;
        
        Entry(const std::string& key, List::Node* node) : key(key), node(node), next(nullptr) {}
    };

    size_t count;
    size_t capacity;
    Entry** table;
    List::Node** charTable; // Table for storing nodes of 'A'-'Z'

    int hashFunction(const std::string& key) const;
    int getCharIndex(char c) const; // Helper function to get index in charTable
    void resizeAndRehash();
};

#endif
