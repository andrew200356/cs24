#include "Board.h"

#include <iostream>

#include "Errors.h"
#include "Move.h"

// Space for implementing Board functions.
void Board::make_move(const Move &move) {
    // Check if the move is valid
    if (board[move.row - 'A'][move.column - 1] != 0) {
        throw InvalidMove("Invalid move");
    }

    // step is the number of moves made
    step++;
    if (step != move.number) {
        throw InvalidMove("Invalid move number");
    }

    // make sure the player is different with last one
    // check the player is X or O
    if (step > 1 && move.player == turn) {
        throw InvalidMove("Invalid player");
    }

    // Make the move
    board[move.row - 'A'][move.column - 1] = (move.player == 'X') ? 1 : -1;

    // // Print the board
    // for (int i = 0; i < 3; i++)
    // {
    //     for (int j = 0; j < 3; j++)
    //     {
    //         if (board[i][j] == 1)
    //         {
    //             std::cout << 'X' << ' ';
    //         }
    //         else if (board[i][j] == -1)
    //         {
    //             std::cout << 'O' << ' ';
    //         }
    //         else
    //         {
    //             std::cout << '_' << ' ';
    //         }
    //     }
    //     std::cout << '\n';
    // }

    // Check if there is a winner
    // if one rows of cols or diagonals add up to 3 or -3, then there is a winner
    for (int i = 0; i < 3; i++) {
        if (board[i][0] + board[i][1] + board[i][2] == 3 || board[0][i] + board[1][i] + board[2][i] == 3 || board[0][0] + board[1][1] + board[2][2] == 3 || board[0][2] + board[1][1] + board[2][0] == 3) {
            winnder = 1;
            return;
        }
        if (board[i][0] + board[i][1] + board[i][2] == -3 || board[0][i] + board[1][i] + board[2][i] == -3 || board[0][0] + board[1][1] + board[2][2] == -3 || board[0][2] + board[1][1] + board[2][0] == -3) {
            winnder = -1;
            return;
        }
    }

    // Check if it is a draw
    if (step == 9) {
        winnder = 9;
    }
}

void Board::set_turn(const Move &move) {
    turn = move.player;
}

int Board::get_turn() {
    return turn;
}

int Board::get_winner() {
    return winnder;
}

bool Board::is_empty() {
    return step == 0;
}