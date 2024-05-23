#include "Index.h"

#include <cstdint>
#include <cstring>   // For memset
#include <string>

uint32_t xxHash32(const std::string& input, uint32_t seed = 0) {
    const uint32_t PRIME32_1 = 2654435761U;
    const uint32_t PRIME32_2 = 2246822519U;
    const uint32_t PRIME32_3 = 3266489917U;
    const uint32_t PRIME32_4 = 668265263U;
    const uint32_t PRIME32_5 = 374761393U;

    const size_t length = input.size();
    const uint8_t* data = reinterpret_cast<const uint8_t*>(input.data());

    uint32_t hash;
    size_t remaining = length;

    if (length >= 16) {
        const uint8_t* end = data + length - 16;
        uint32_t v1 = seed + PRIME32_1 + PRIME32_2;
        uint32_t v2 = seed + PRIME32_2;
        uint32_t v3 = seed + 0;
        uint32_t v4 = seed - PRIME32_1;

        do {
            v1 += *reinterpret_cast<const uint32_t*>(data) * PRIME32_2;
            v1 = (v1 << 13) | (v1 >> 19);
            v1 *= PRIME32_1;
            data += 4;

            v2 += *reinterpret_cast<const uint32_t*>(data) * PRIME32_2;
            v2 = (v2 << 13) | (v2 >> 19);
            v2 *= PRIME32_1;
            data += 4;

            v3 += *reinterpret_cast<const uint32_t*>(data) * PRIME32_2;
            v3 = (v3 << 13) | (v3 >> 19);
            v3 *= PRIME32_1;
            data += 4;

            v4 += *reinterpret_cast<const uint32_t*>(data) * PRIME32_2;
            v4 = (v4 << 13) | (v4 >> 19);
            v4 *= PRIME32_1;
            data += 4;
        } while (data <= end);

        hash = (v1 << 1) | (v1 >> 31);
        hash += (v2 << 7) | (v2 >> 25);
        hash += (v3 << 12) | (v3 >> 20);
        hash += (v4 << 18) | (v4 >> 14);
    } else {
        hash = seed + PRIME32_5;
    }

    hash += static_cast<uint32_t>(length);

    while (remaining >= 4) {
        hash += *reinterpret_cast<const uint32_t*>(data) * PRIME32_3;
        hash = (hash << 17) | (hash >> 15);
        hash *= PRIME32_4;
        data += 4;
        remaining -= 4;
    }

    while (remaining > 0) {
        hash += (*data) * PRIME32_5;
        hash = (hash << 11) | (hash >> 21);
        hash *= PRIME32_1;
        data++;
        remaining--;
    }

    hash ^= hash >> 15;
    hash *= PRIME32_2;
    hash ^= hash >> 13;
    hash *= PRIME32_3;
    hash ^= hash >> 16;

    return hash;
}
// Primary hash function (FNV-1a)
int Index::hashFunction(const std::string& key) const {
    return static_cast<int>(xxHash32(key));
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
    // std::memset(charTable, 0, 52);  // Initialize charTable
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
// Path: labs/counter/Index.cpp