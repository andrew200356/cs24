#include "Heap.h"

#include <algorithm>
#include <stdexcept>

// Constructor to initialize the heap with a given capacity
Heap::Heap(size_t capacity) : mData(new Entry[capacity]), mCapacity(capacity), mCount(0){};

// Copy constructor
Heap::Heap(const Heap& other) : mCapacity(other.mCapacity), mCount(other.mCount) {
    // traditional way
    // for (size_t i = 0; i < mCount; i++) {
    //     mData[i] = other.mData[i];
    // }

    // using std::copy
    mData = new Entry[mCapacity];
    std::copy(other.mData, other.mData + mCount, mData);
}

// Destructor to free the allocated memory
Heap::~Heap() {
    delete[] mData;
}

// Returns the maximum capacity of the heap
size_t Heap::capacity() const {
    return mCapacity;
}

// Returns the current number of items in the heap
size_t Heap::count() const {
    return mCount;
}

// Returns a reference to the entry at a given index
const Heap::Entry& Heap::lookup(size_t index) const {
    if (index >= mCount) {
        throw std::out_of_range("Index out of range");
    }
    return mData[index];
}

// Removes and returns the entry with the lowest score
Heap::Entry Heap::pop() {
    if (mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }
    Entry result = mData[0];
    mData[0] = mData[--mCount];
    if (mCount > 0) {
        // Helper function to move an entry down the heap to maintain heap property
        auto percolate_down = [this](size_t index) {
            while (true) {
                size_t left = index * 2 + 1;
                size_t right = index * 2 + 2;
                size_t smallest = index;

                if (left < mCount && mData[left].score < mData[smallest].score) {
                    smallest = left;
                }
                if (right < mCount && mData[right].score < mData[smallest].score) {
                    smallest = right;
                }
                if (smallest == index) {
                    break;
                }
                std::swap(mData[smallest], mData[index]);
                index = smallest;
            }
        };
        percolate_down(0);
    }
    return result;
}

// Adds a new entry to the heap
void Heap::push(const std::string& value, float score) {
    if (mCount == mCapacity) {
        throw std::overflow_error("Heap is full");
    }
    mData[mCount] = {value, score};
    // Helper function to move an entry up the heap to maintain heap property
    auto percolate_up = [this](size_t index) {
        while (index > 0) {
            size_t parent = (index - 1) / 2;
            if (mData[parent].score <= mData[index].score) {
                break;
            }
            std::swap(mData[parent], mData[index]);
            index = parent;
        }
    };
    percolate_up(mCount++);
}

// Efficient version of a pop followed by a push
Heap::Entry Heap::pushpop(const std::string& value, float score) {
    if (mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }
    Entry result = mData[0];
    if (score > result.score) {
        mData[0] = {value, score};
        // Re-use the percolate_down helper function from pop
        auto percolate_down = [this](size_t index) {
            while (true) {
                size_t left = index * 2 + 1;
                size_t right = index * 2 + 2;
                size_t smallest = index;

                if (left < mCount && mData[left].score < mData[smallest].score) {
                    smallest = left;
                }
                if (right < mCount && mData[right].score < mData[smallest].score) {
                    smallest = right;
                }
                if (smallest == index) {
                    break;
                }
                std::swap(mData[smallest], mData[index]);
                index = smallest;
            }
        };
        percolate_down(0);
    }
    return result;
}

// Returns a reference to the entry with the lowest score
const Heap::Entry& Heap::top() const {
    if (mCount == 0) {
        throw std::underflow_error("Heap is empty");
    }
    return mData[0];
}