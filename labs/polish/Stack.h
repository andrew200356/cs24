#ifndef STACK_H
#define STACK_H

#include "AST.h"

// Use this file to define your Stack type.
// Implement its member functions in Stack.cpp.

class Stack {
    struct Node {
        AST* ast;
        Node* next;
    };

   private:
    Node* m_top;

   public:
    Stack();
    ~Stack();

    void push(AST* ast);
    AST* pop();
    AST* top() const;
    bool is_empty() const;
    bool only_one() const;
};
#endif
