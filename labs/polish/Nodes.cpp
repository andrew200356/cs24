#include "Nodes.h"

#include <cmath>
#include <iostream>
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

BinaryOp ::~BinaryOp() {
    delete left;
    delete right;
}

std::string BinaryOp ::prefix() const {
    // AST::prefix() returns a string representation of the subtree rooted at the node. This string is in Polish notation, with tokens separated by single spaces.
    return std::string(1, op) + " " + left->prefix() + " " + right->prefix();
}

std::string BinaryOp ::postfix() const {
    // AST::postfix() returns a string representation of the subtree rooted at the node. This string is in reverse Polish notation, with tokens separated by single spaces.
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
        // throw a std::runtime_error with the message Division by zero when the right operand is zero
        if (right->value() == 0) {
            throw std::runtime_error("Division by zero.");
        }
        return fmod(left->value(), right->value());
    }
    return 0;
}

Negate ::Negate(AST* operand) : operand(operand) {}

Negate ::~Negate() {
    delete operand;
}

std::string Negate ::prefix() const {
    return "~ " + operand->prefix();
}

std::string Negate ::postfix() const {
    return operand->postfix() + " ~";
}

double Negate ::value() const {
    return -operand->value();
}