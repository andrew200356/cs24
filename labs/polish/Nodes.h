#ifndef NODES_H
#define NODES_H

#include "AST.h"

// Declare your AST subclasses here.
// Implement their member functions in Nodes.cpp.

class Number : public AST {
    double m_value;

   public:
    Number(double value);

    std::string prefix() const;
    std::string postfix() const;
    double value() const;
};

class Negate : public AST {
    AST* operand;

   public:
    Negate(AST* operand);
    ~Negate();

    std::string prefix() const;
    std::string postfix() const;
    double value() const;
};

class BinaryOp : public AST {
    char op;
    AST* left;
    AST* right;

   public:
    BinaryOp(char op, AST* left, AST* right);
    ~BinaryOp();
    std::string prefix() const;
    std::string postfix() const;
    double value() const;
};

#endif
