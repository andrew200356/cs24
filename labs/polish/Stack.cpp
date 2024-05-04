#include "Stack.h"

#include <stdexcept>

// Implement your Stack member functions here.
Stack ::Stack() : m_top(nullptr) {}

Stack ::~Stack() {
    Node* current = m_top;
    while (current) {
        // increment the top pointer
        Node* temp = current;
        current = current->next;

        // delete the AST object and the Node object
        delete temp->ast;
        delete temp;
    }
}

void Stack ::push(AST* ast) {
    // create a new node
    // set the top pointer to the new node
    m_top = new Node{ast, m_top};
}

AST* Stack ::pop() {
    // check if the stack is empty
    if (m_top == nullptr) {
        // when you try to pop from an empty stack, the parsing must took too much
        throw std::runtime_error("Not enough operands.");
        return nullptr;
    }

    // get the top node
    Node* temp = m_top;
    AST* ast = temp->ast;

    // increment the top pointer
    m_top = m_top->next;

    // delete the node
    delete temp;

    return ast;
}

AST* Stack ::top() const {
    // check if the stack is empty
    if (m_top == nullptr) {
        return nullptr;
    }

    return m_top->ast;
}

bool Stack ::is_empty() const {
    return m_top == nullptr;
}

bool Stack ::only_one() const {
    return m_top != nullptr && m_top->next == nullptr;
}