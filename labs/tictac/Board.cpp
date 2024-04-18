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

    // Make the move
    board[move.row - 'A'][move.column - 1] = (move.player == 'X') ? 1 : -1;
}

int Board::get_winner()
{
    return winnder;
}

bool Board::is_empty()
{
    return move == 0;
}