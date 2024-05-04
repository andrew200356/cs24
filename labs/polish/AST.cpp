#include "AST.h"

#include <sstream>
#include <string>

#include "Nodes.h"
#include "Stack.h"

AST* AST::parse(const std::string& expression) {
    Stack stack;
    std::string token;
    std::istringstream stream(expression);

    while (stream >> token) {  // breaks expression into tokens
        // the input is in Reverse Polish Notation which is a bit hard to parse directly
        // so we can parse it into token and store directly into an AST
        // and we can use a stack to store the ASTs
        // then we can pop the ASTs from the stack and combine them into a single AST
        // this is a common way to parse RPN

        if (token.find_first_not_of("0123456789.") == std::string::npos) {
            // start with checking if token that is number
            // if it is a number, create a Number object and push it onto the stack
            stack.push(new Number(std::stod(token)));
        } else if (token == "~") {
            // if the token is a negate operator, pop the top AST from the stack
            AST* arg = stack.pop();
            // create a Negate object with the top AST as its argument
            stack.push(new Negate(arg));

            // If the token is an operator, the function pops its arguments off of the stack and pushes the new operator onto the stack.
        } else if (token == "+") {
            AST* right = stack.pop();
            AST* left = stack.pop();
            // create a BinaryOp object with the top two ASTs as its arguments
            stack.push(new BinaryOp('+', left, right));
        } else if (token == "-") {
            AST* right = stack.pop();
            AST* left = stack.pop();
            // create a BinaryOp object with the top two ASTs as its arguments
            stack.push(new BinaryOp('-', left, right));
        } else if (token == "*") {
            AST* right = stack.pop();
            AST* left = stack.pop();
            // create a BinaryOp object with the top two ASTs as its arguments
            stack.push(new BinaryOp('*', left, right));
        } else if (token == "/") {
            AST* right = stack.pop();
            AST* left = stack.pop();
            // create a BinaryOp object with the top two ASTs as its arguments
            stack.push(new BinaryOp('/', left, right));
        } else if (token == "%") {
            AST* right = stack.pop();
            AST* left = stack.pop();
            // create a BinaryOp object with the top two ASTs as its arguments
            stack.push(new BinaryOp('%', left, right));
        } else {
            // If you encounter an invalid token, say Invalid token: XXX, where XXX is the invalid token.
            throw std::runtime_error("Invalid token: " + token);
        }

        // if the token is a number, create a Number object and push it onto the stack
    }

    // When it reaches the end of the string, there should be exactly one AST node on the stack: this is the root of the final AST.

    // You may run into some invalid inputs while parsing. When you do, throw a std::runtime_error with the appropriate error message:

    if (stack.is_empty()) {
        // If there is nothing on the stack at the end of parsing, say No input.
        throw std::runtime_error("No input");
    } else if (!stack.only_one()) {
        // If there are multiple nodes on the stack at the end of parsing, say Too many operands.
        throw std::runtime_error("Too many operands");
    }
    return stack.pop();
};

// notes for the parse function:
