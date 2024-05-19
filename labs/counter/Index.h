#ifndef INDEX_H
#define INDEX_H

#include <cstddef>
#include <string>

#include "List.h"

extern List::Node* const DIRTY;

class Index {
    int count;
    int capacity;
    List::Node** table;

   public:
    Index(int capacity = 1000);
    ~Index();
    void resizeAndRehash();
    int hashFunction(const std::string& key) const;
    void insert_i(const std::string& key, int value, List* list);
    List::Node* find(const std::string& key) const;
    List::Node* remove_i(const std::string& key, List* list);
    void remove(int index, List* list);
    int getCount();
    int getTotal();
    void debugPrint() const;
};

#endif
