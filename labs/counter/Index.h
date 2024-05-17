#ifndef INDEX_H
#define INDEX_H

#include <cstddef>
#include <string>

#include "List.h"

// TODO...
class Index {
   private:
    // Member Variables
    int count;           // Number of elements in the index
    int capacity;        // Capacity of the index
    List::Node** table;  // hash table storing the pointer to the list nodes

   public:
    Index(int capacity = 1000);
    ~Index();

    // Member Functions
    void insert_index(const std::string& key, int value, List* list);
    void insert_i(const std::string& key, int value, List* list);
    List::Node* find(const std::string& key) const;
    List::Node* remove_index(const std::string& key, List* list);
    void remove_i(const std::string& key, List* list);
    int getCount();
    int getTotal();

    // Helper Functions
    void resizeAndRehash();
    int hashFunction1(const std::string& key) const;
    int hashFunction2(const std::string& key) const;
};

#endif
