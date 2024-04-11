#ifndef FIBVEC_H
#define FIBVEC_H

// This provides the size_t type:
#include <cstddef>

/*
Your vector must obey the following rules:
    The vector must always have a capacity that is a Fibonacci number.
    The vector must always have a capacity greater than or equal to f(2) = 1.
    When inserting into a vector with capacity f(n): if there is no room for the item, the vector must resize its capacity to the next Fibonacci number (f(n+1)).
    When removing from a vector with capacity f(n): if the number of items drops below f(n-2), the vector must resize its capacity to f(n-1).
*/
class FibVec
{
    // Member Variables
    size_t m_count;
    size_t m_capacity;
    int *m_data;
    int num1;
    int num2;

    // Helper Functions
    void resize();
    void downsize();

public:
    // Constructor and Destructor
    FibVec();
    ~FibVec();
    // Member Functions
    size_t capacity() const;
    size_t count() const;
    void insert(int value, size_t index);
    size_t lookup(size_t index) const;
    int pop();
    void push(int value);
    int remove(size_t index);
};

#endif
