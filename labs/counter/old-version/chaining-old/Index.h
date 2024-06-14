// Index.h

#ifndef INDEX_H
#define INDEX_H

#include "List.h"

class Index {
    struct Chain {
        List::Node* node;
        Chain* next;

        Chain(List::Node* node = nullptr, Chain* next = nullptr)
            : node(node), next(next) {}
    };

    int count;
    int capacity;
    Chain** table;  // hash table for the index
    mutable List::Node* wanted = nullptr;

   public:
    Index(int capacity = 85000);
    ~Index();
    void resizeAndRehash();
    int hashFunction(const std::string& key) const;
    void insert_i(const std::string& key, int value, List* list);
    void set_i(const std::string& key, int value, List* list);
    List::Node* find(const std::string& key) const;
    void remove_i(const std::string& key, List* list);
    int getCount();
    int getTotal();
};

#endif
