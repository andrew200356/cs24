// Index.h

#ifndef INDEX_H
#define INDEX_H

#include <cstddef>
#include <string>

#include "List.h"

class Index {
   public:
    int count;
    int capacity;
    List::Node** table;              // hash table for the index
    static List::Node* const DIRTY;  // Sentinel for dirty nodes

    Index(int capacity = 1000);
    ~Index();
    void resizeAndRehash();
    int hashFunction(const std::string& key) const;
    void insert_i(const std::string& key, int value, List* list);
    void set_i(const std::string& key, int value, List* list);
    List::Node* find(const std::string& key) const;
    void remove_i(const std::string& key, List* list);
    int getCount();
    int getTotal();
    void debugPrint() const;
};

#endif
