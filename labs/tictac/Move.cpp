#include "Errors.h"
#include "Move.h"
#include <iostream>
// Space for implementing Move functions.
Move::Move(const std::string &input)
{
    // Parse the input string to initialize the Move.
    // The input string will be in the format "number player square [comment]".

    /*
    Move Format
    A move is represented as a single line of text in the following format. The term "whitespace" means one or more characters that are considered spaces by the isspace() function from the cctype header and/or the std::ws helper from the istream header.

    The move number. This is an integer between 1 and 9, inclusive, with no sign.
    Whitespace.
    The player code. This is either an X or an O; lower case is also allowed.
    Whitespace.
    The square code. This is a letter followed by a digit. Letters represent rows, with row A being the top row, B the middle, and C the bottom; lower case is also allowed. Digits represent columns, with 1 being the left column, 2 the middle, and 3 the right.
    Optionally, whitespace.
    Optionally, a comment. This is any text beginning with the # character and extending to the end of the string. If a comment is present, the preceding whitespace is required.
    When printing moves, your program should use the same format. When whitespace is required, it should always print a single space character. It should never print comments or the whitespace that precedes them. Player and row codes should be in upper case.
    */

    std::istringstream iss(input);

    // Initialize a string array to store each part if iss
    char parts[6];
    // whitespace represent by std::ws
    // iss >> parts[0] >> std::ws >> parts[2] >> std::ws >> parts[4] >> parts[5];
    for (int i = 0; i < 6; i++)
    {
        parts[i] = iss.get();
        if (isspace(parts[i]))
        {
            iss >> std::ws;
        }
        // std::cout << "parts" << i << "is" << parts[i] << " ";
    }
    // iss >> number >> std::ws >> player >> std::ws >> row >> column;

    // check white space
    if ((isspace(parts[1]) + isspace(parts[3])) == 0)
    {
        throw ParseError("Invalid whitespace");
    }

    // number has to between 1 and 9
    number = parts[0] - '0';
    if (number < 1 || number > 9)
    {
        throw ParseError("Invalid move number");
    }

    // player has to be X or O
    player = std::toupper(parts[2]);
    if (player != 'X' && player != 'O')
    {
        throw ParseError("Invalid player code");
    }

    // row has to be A, B, or C
    row = std::toupper(parts[4]);
    if (row != 'A' && row != 'B' && row != 'C')
    {
        throw ParseError("Invalid row code");
    }

    // column has to be 1, 2, or 3
    column = parts[5] - '0';
    if (column < 1 || column > 3)
    {
        throw ParseError("Invalid column number");
    }

    // Check if there is more to read and a comment marker
    std::string comment;
    std::getline(iss, comment);
    if (!comment.empty() && (isspace(comment[0]) || comment[1] != '#'))
    {
        throw ParseError("Invalid comment");
    }

}

// Convert Move object back to a string in the correct format
std::string Move::to_string() const
{
    std::ostringstream oss;
    oss << number << " " << player << " " << char(row) << column;
    return oss.str();
}