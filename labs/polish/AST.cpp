#include "AST.h"

#include <sstream>

#include "Nodes.h"
#include "Stack.h"

// parse helper function
// this function is used to parse the string into a double
double parse_double(const std::string& token) {
    try {
        size_t len = 0;
        double number = std::stod(token, &len);  // now len is the length of the number
        if (len == token.length()) {             // if the length of the number is the same as the length of the token
            return number;
        }
    } catch (const std::invalid_argument& error) {
        //     throw std::runtime_error("Invalid token: " + token);
        // } catch (const std::out_of_range& error) {
        //     throw std::runtime_error("Invalid token: " + token);
    }

    // If the token is not a number, throw a std::runtime_error with the message Invalid token: followed by the token.
    throw std::runtime_error("Invalid token: " + token);
}

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

        if (token == "~") {
            // if the token is a negate operator, pop the top AST from the stack
            AST* arg = stack.pop();
            // create a Negate object with the top AST as its argument
            stack.push(new Negate(arg));

            // If the token is an operator, the function pops its arguments off of the stack and pushes the new operator onto the stack.
        } else if (token == "+") {
            AST* right = stack.pop();
            if (stack.is_empty()) {  // if the stack is empty, there is no left operand so throw an error
                delete right;
                throw std::runtime_error("Not enough operands.");
            }
            AST* left = stack.pop();
            stack.push(new BinaryOp('+', left, right));
        } else if (token == "-") {
            AST* right = stack.pop();
            if (stack.is_empty()) {  // if the stack is empty, there is no left operand so throw an error
                delete right;
                throw std::runtime_error("Not enough operands.");
            }
            AST* left = stack.pop();
            stack.push(new BinaryOp('-', left, right));
        } else if (token == "*") {
            AST* right = stack.pop();
            if (stack.is_empty()) {  // if the stack is empty, there is no left operand so throw an error
                delete right;
                throw std::runtime_error("Not enough operands.");
            }
            AST* left = stack.pop();
            stack.push(new BinaryOp('*', left, right));
        } else if (token == "/") {
            AST* right = stack.pop();
            if (stack.is_empty()) {  // if the stack is empty, there is no left operand so throw an error
                delete right;
                throw std::runtime_error("Not enough operands.");
            }
            AST* left = stack.pop();
            stack.push(new BinaryOp('/', left, right));
        } else if (token == "%") {
            AST* right = stack.pop();
            if (stack.is_empty()) {  // if the stack is empty, there is no left operand so throw an error
                delete right;
                throw std::runtime_error("Not enough operands.");
            } else if (right->value() == 0) {
                delete right;
                throw std::runtime_error("Division by zero.");
            }
            AST* left = stack.pop();

            stack.push(new BinaryOp('%', left, right));
        } else {
            // if the token is a number, create a Number object and push it onto the stack
            stack.push(new Number(parse_double(token)));
        }
    }

    // When it reaches the end of the string, there should be exactly one AST node on the stack: this is the root of the final AST.

    // You may run into some invalid inputs while parsing. When you do, throw a std::runtime_error with the appropriate error message:

    if (stack.is_empty()) {
        // If there is nothing on the stack at the end of parsing, say No input.

        throw std::runtime_error("No input.");
    } else if (!stack.only_one()) {
        // If there are multiple nodes on the stack at the end of parsing, say Too many operands.

        throw std::runtime_error("Too many operands.");
    }
    return stack.pop();
};
