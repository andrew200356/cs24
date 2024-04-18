#include "Errors.h"
#include "Board.h"

// Space for implementing Board functions.
void Board::make_move(const Move &move)
{
    // Check if the move is valid
    if (board[move.row - 'A'][move.column - 1] != 0)
    {
        throw InvalidMove("Invalid move");
    }

    // step is the number of moves made
    step++;
    if (step != move.number)
    {
        throw InvalidMove("Invalid move number");
    }
    // Make the move
    board[move.row - 'A'][move.column - 1] = (move.player == 'X') ? 1 : -1;
    // Check if the game is over
    // if rows of cols or diagonals add up to 3 or -3, then there is a winner
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] + board[i][1] + board[i][2] == 3 || board[0][i] + board[1][i] + board[2][i] == 3 || board[0][0] + board[1][1] + board[2][2] == 3 || board[0][2] + board[1][1] + board[2][0] == 3)
        {
            winnder = 1;
            return;
        }
        if (board[i][0] + board[i][1] + board[i][2] == -3 || board[0][i] + board[1][i] + board[2][i] == -3 || board[0][0] + board[1][1] + board[2][2] == -3 || board[0][2] + board[1][1] + board[2][0] == -3)
        {
            winnder = -1;
            return;
        }
    }
}

void Board::set_turn(const Move &move)
{
    turn = (move.player == 'X') ? -1 : 1;
}

int Board::get_turn()
{
    return turn;
}

int Board::get_winner()
{
    return winnder;
}

bool Board::is_empty()
{
    return step == 0;
}