#ifndef INDEX_H
#define INDEX_H

#include <cstddef>
#include <string>

#include "List.h"

// TODO...
class Index {
   private:
    // Member Variables
    size_t count;        // Number of elements in the index
    size_t capacity;     // Capacity of the index
    List::Node** table;  // hash table storing the pointer to the list nodes

   public:
    Index(int capacity = 1000);
    ~Index();
    // TODO: Implement hashFunction, insert, find, and remove methods
    size_t hashFunction(const std::string& key) const;
    void insert_index(const std::string& key, int value, List* list);
    List::Node* find(const std::string& key) const;
    List::Node* remove_index(const std::string& key, List* list);
};

#endif
