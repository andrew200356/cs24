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

class BinaryOp : public AST {
   public:
    AST* left;
    AST* right;
    std::string prefix() const;
    std::string postfix() const;
};

class Add : public BinaryOp {
   public:
    Add(AST* left, AST* right);
    double value() const;
};

class Subtract : public BinaryOp {
   public:
    Subtract(AST* left, AST* right);
    double value() const;
};

class Multiply : public BinaryOp {
   public:
    Multiply(AST* left, AST* right);
    double value() const;
};

class Divide : public BinaryOp {
   public:
    Divide(AST* left, AST* right);
    double value() const;
};

class Modulo : public BinaryOp {
   public:
    Modulo(AST* left, AST* right);
    double value() const;
};

class Negate : public AST {
    AST* operand;

   public:
    Negate(AST* operand);

    std::string prefix() const;
    std::string postfix() const;
    double value() const;
};
#endif
