#ifndef INDEX_H
#define INDEX_H

#include <cstddef>

// TODO...
class Index {
   private:
    // Member Variables
    size_t count;     // Number of elements in the index
    size_t capacity;  // Capacity of the index
    // hash table storing the pointer to the list nodes

   public:
    Index();
    ~Index();
};

#endif
