#include "Board.h"
#include "Errors.h"
#include "Move.h"
#include <iostream>
#include <string>

int main()
{
    /*
    The evaluator reads a game from standard input one line at a time. If the line cannot be parsed as a move, it prints Parse error. and exits with status code one. If the move is invalid according to the game rules, as defined below, it prints Invalid move. and exits with status code two.

    If the evaluator reaches the end of its input without encountering an error, it prints the result of the game and exits with status code 0. The possible results are:

    Game in progress: New game. If no moves have been made.
    Game in progress: X's turn. If it is Player X's turn to play.
    Game in progress: O's turn. If it is Player O's turn to play.
    Game over: X wins. If the game is over and Player X won.
    Game over: O wins. If the game is over and Player O won.
    Game over: Draw. If the game is over and neither player won.
    */

    Board board = Board();
    std::string line;
    while (std::getline(std::cin, line))
    {
        try
        {
            Move move = Move(line);
            board.make_move(move);
        }
        catch (const ParseError &e)
        {
            std::cout << "Parse error.\n";
            return 1;
        }
        catch (const InvalidMove &e)
        {
            std::cout << "Invalid move.\n";
            return 2;
        }
    }
}
