#include "Index.h"

#include <cstdint>

constexpr uint32_t FNV_32_OFFSET_BASIS = 0x811c9dc5;
constexpr uint32_t FNV_32_PRIME = 0x01000193;

// Primary hash function (FNV-1a)
int Index::hashFunction(const std::string& key) const {
    uint32_t hash = FNV_32_OFFSET_BASIS;
    for (char c : key) {
        hash ^= static_cast<uint32_t>(c);
        hash *= FNV_32_PRIME;
    }
    return static_cast<int>(hash);
}

// Helper function to get index in charTable
int Index::getCharIndex(char c) const {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    } else if (c >= 'a' && c <= 'z') {
        return c - 'a' + 26;
    }
    return -1;
}

Index::Index(int capacity) : count(0), capacity(capacity) {
    table = new Entry*[capacity]();
    charTable = new List::Node*[52]();
}

Index::~Index() {
    for (size_t i = 0; i < capacity; ++i) {
        Entry* entry = table[i];
        while (entry) {
            Entry* next = entry->next;
            delete entry;
            entry = next;
        }
    }
    delete[] table;
    delete[] charTable;
}

List::Node* Index::find(const std::string& key) const {
    if (key.size() == 1) {
        char k = key[0];
        int charIndex = getCharIndex(k);
        if (charIndex != -1) {
            return charTable[charIndex];
        }
    }

    int index = hashFunction(key) % capacity;
    Entry* entry = table[index];
    while (entry) {
        if (entry->key == key) {
            return entry->node;
        }
        entry = entry->next;
    }
    return nullptr;
}

void Index::push(const std::string& key, List::Node* node) {
    if (key.size() == 1) {
        char k = key[0];
        int charIndex = getCharIndex(k);
        if (charIndex != -1) {
            charTable[charIndex] = node;
            return;
        }
    }

    if (static_cast<double>(count) / capacity > 0.6) {
        resizeAndRehash();
    }

    int index = hashFunction(key) % capacity;
    Entry* newEntry = new Entry(key, node);
    newEntry->next = table[index];
    table[index] = newEntry;
    ++count;
}

void Index::remove(const std::string& key) {
    if (key.size() == 1) {
        char k = key[0];
        int charIndex = getCharIndex(k);
        if (charIndex != -1) {
            charTable[charIndex] = nullptr;
            return;
        }
    }

    int index = hashFunction(key) % capacity;
    Entry* entry = table[index];
    Entry* prev = nullptr;

    while (entry) {
        if (entry->key == key) {
            if (prev) {
                prev->next = entry->next;
            } else {
                table[index] = entry->next;
            }
            delete entry;
            --count;
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

void Index::resizeAndRehash() {
    size_t oldCapacity = capacity;
    Entry** oldTable = table;

    capacity = (count + 1) * 2;
    table = new Entry*[capacity]();

    for (size_t i = 0; i < oldCapacity; ++i) {
        Entry* entry = oldTable[i];
        while (entry) {
            Entry* next = entry->next;
            int index = hashFunction(entry->key) % capacity;
            entry->next = table[index];
            table[index] = entry;
            entry = next;
        }
    }
    delete[] oldTable;
}
