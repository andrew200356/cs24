#include "Index.h"

#include <cstdint>
#include <cstring>   // For memset
#include <iostream>  // For debug output
#include <string>

uint32_t MurmurHash3(const std::string& key, uint32_t seed = 0) {
    const uint8_t* data = (const uint8_t*)key.c_str();
    const int len = key.size();
    const int nblocks = len / 4;
    uint32_t h1 = seed;

    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;

    const uint32_t* blocks = (const uint32_t*)(data + nblocks * 4);
    for (int i = -nblocks; i; i++) {
        uint32_t k1 = blocks[i];

        k1 *= c1;
        k1 = (k1 << 15) | (k1 >> (32 - 15));
        k1 *= c2;

        h1 ^= k1;
        h1 = (h1 << 13) | (h1 >> (32 - 13));
        h1 = h1 * 5 + 0xe6546b64;
    }

    const uint8_t* tail = (const uint8_t*)(data + nblocks * 4);
    uint32_t k1 = 0;

    switch (len & 3) {
        case 3:
            k1 ^= tail[2] << 16;
            [[fallthrough]];
        case 2:
            k1 ^= tail[1] << 8;
            [[fallthrough]];
        case 1:
            k1 ^= tail[0];
            k1 *= c1;
            k1 = (k1 << 15) | (k1 >> (32 - 15));
            k1 *= c2;
            h1 ^= k1;
    }

    h1 ^= len;

    h1 ^= h1 >> 16;
    h1 *= 0x85ebca6b;
    h1 ^= h1 >> 13;
    h1 *= 0xc2b2ae35;
    h1 ^= h1 >> 16;

    return h1;
}

int Index::hashFunction(const std::string& key) const {
    return static_cast<int>(MurmurHash3(key));
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
    std::memset(charTable, 0, 52);  // Initialize charTable
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

    if (static_cast<double>(count) / capacity > 0.7) {
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