#include "Counter.h"

// Counter Member Functions
Counter::Counter() {
    // The default constructor creates an empty Counter.
}

Counter::~Counter() {
    // The destructor should free all memory allocated by the Counter.
}

Counter::Iterator Counter::begin() const {
    // The begin() function should return an iterator to the first-inserted item in the counter.
}

size_t Counter::count() const {
    // The count() function should return the number of keys stored in the counter.
}

void Counter::dec(const std::string& key, int by) {
    // dec(k, d) decrements a count by a given value (default one).
}

void Counter::del(const std::string& key) {
    // del(k) removes a key from the counter, setting its count to (implicit) zero.
}

// end() returns an invalid "end" iterator (see below).
Counter::Iterator Counter::end() const {
    // The end() function should return an iterator to the "end" of the counter.
}

// get(k) looks up a count by key. If the key isn't present, it returns zero.
int Counter::get(const std::string& key) const {
    // get(k) looks up a count by key. If the key isn't present, it returns zero.
}

// inc(k, d) increments a count by a given value (default one).
void Counter::inc(const std::string& key, int by) {
    // inc(k, d) increments a count by a given value (default one).
}

// set(k, v) sets a count by key.
void Counter::set(const std::string& key, int count) {
    // set(k, v) sets a count by key.
}

// total() returns the sum of all counts in the counter.
int Counter::total() const {
    // total() returns the sum of all counts in the counter.
}

// The inc(), dec(), and set() functions will add keys to the counter if they are not already present.
// The del() function is the only function that removes keys; setting a value to zero does not remove the corresponding key.