#ifndef COUNTER_H
#define COUNTER_H

#include <cstddef>
#include <iostream>
#include <string>

#include "Index.h"
#include "List.h"

// This is the Counter class you need to implement.
// It includes the Counter::Iterator as a nested class.

class Counter {
    // Member Variables
    List* list;  // Declare the List for the Counter
    Index* index;  // Declare the Index for the Counter

   public:
    class Iterator {
        // Member Variables
        List::Node* current;

       public:
        // Constructor
        Iterator(List::Node* current);

        const std::string& key() const;
        int value() const;

        void operator++();
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };

   private:
    // Member Variables

   private:
    // Helper Functions

   public:
    Counter();
    ~Counter();

    size_t count() const;
    int total() const;

    void inc(const std::string& key, int by = 1);
    void dec(const std::string& key, int by = 1);
    void del(const std::string& key);
    int get(const std::string& key) const;
    void set(const std::string& key, int count);
    void print() const;  // debug print
    void listkeys() const;  // debug print

    Iterator begin() const;
    Iterator end() const;
};

#endif
