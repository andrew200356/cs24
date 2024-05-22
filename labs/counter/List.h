// List.h

#ifndef LIST_H
#define LIST_H

#include <string>

class List {
   public:
    // Node class
    class Node {
       public:
        std::string key;
        int value;
        Node* next;
        Node* prev;

        // Constructor
        Node(const std::string& key, int value, Node* next = nullptr, Node* prev = nullptr)
            : key(key), value(value), next(next), prev(prev) {}
    };

    Node* head;
    Node* tail;
    size_t size;
    
    // Constructor
    List();
    // Destructor
    ~List();

    // Member Functions
    Node* find(const std::string& key) const;
    Node* push(const std::string& key, int value);
    void remove(Node* node);
    int getTotal() const;
    size_t getSize() const;
};

#endif
