#include "Nodes.h"

#include <sstream>
#include <string>

// This creates the number format the autograder expects:
std::string format(double number) {
    std::ostringstream stream;
    stream << number;
    return stream.str();
}

// Implement your AST subclasses' member functions here.
Number ::Number(double value) : m_value(value) {}

std::string Number ::prefix() const {
    return format(m_value);
}

std::string Number ::postfix() const {
    return format(m_value);
}

double Number ::value() const {
    return m_value;
}

BinaryOp ::BinaryOp(char op, AST* left, AST* right) : op(op), left(left), right(right) {}

std::string BinaryOp ::prefix() const {
    return "(" + std::string(1, op) + " " + left->prefix() + " " + right->prefix() + ")";
}

std::string BinaryOp ::postfix() const {
    return left->postfix() + " " + right->postfix() + " " + std::string(1, op);
}

double BinaryOp ::value() const {
    if (op == '+') {
        return left->value() + right->value();
    } else if (op == '-') {
        return left->value() - right->value();
    } else if (op == '*') {
        return left->value() * right->value();
    } else if (op == '/') {
        return left->value() / right->value();
    } else if (op == '%') {
        return (int)left->value() % (int)right->value();
    }
    return 0;
}