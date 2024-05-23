// Index.h

#ifndef INDEX_H
#define INDEX_H

#include <cstddef>
#include <string>

#include "List.h"

class Index {
   public:
    static List::Node* const DIRTY;  // Sentinel for dirty nodes

    Index(int capacity = 85000);
    ~Index();

    void push(const std::string& key, List::Node* node);
    List::Node* find(const std::string& key) const;
    void remove(const std::string& key);

   private:
    size_t count;
    size_t capacity;
    List::Node** table;
    mutable List::Node* wanted = nullptr;

    int hashFunction(const std::string& key) const;
    int secondaryHashFunction(const std::string& key) const;
    void resizeAndRehash();
};

#endif
