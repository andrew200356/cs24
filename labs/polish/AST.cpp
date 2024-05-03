#include "AST.h"

#include <sstream>

#include "Nodes.h"

AST* AST::parse(const std::string& expression) {
    std::string token;
    std::istringstream stream(expression);

    while (stream >> token) {  // breaks expression into tokens
        // the input is in Reverse Polish Notation which is a bit hard to parse directly
        // so we can parse it into token and store directly into an AST
        // and we can use a stack to store the ASTs
        // then we can pop the ASTs from the stack and combine them into a single AST
        // this is a common way to parse RPN

        // if the token is a number, create a Number object and push it onto the stack
    }
}

// notes for the parse function:
