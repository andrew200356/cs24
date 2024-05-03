#include "Stack.h"

// Implement your Stack member functions here.
Stack ::Stack() : m_top(nullptr) {}

Stack ::~Stack() {
    while (m_top != nullptr) {
        // increment the top pointer
        Node* temp = m_top;
        m_top = m_top->next;

        // delete the AST object and the Node object
        delete temp->ast;
        delete temp;
    }
}

void Stack ::push(AST* ast) {
    // create a new node
    Node* newNode = new Node;
    newNode->ast = ast;
    newNode->next = m_top;

    // set the top pointer to the new node
    m_top = newNode;
}

AST* Stack ::pop() {
    // check if the stack is empty
    if (m_top == nullptr) {
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