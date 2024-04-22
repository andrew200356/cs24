#ifndef BOARD_H
#define BOARD_H

#include "Move.h"

// I recommended writing a Board class to manage your game state.
// Here's some space for the class definition; member functions go in Board.cpp.

class Board {
    // Board class uses a 3 by 3 2d array to represent the board
    // -1 stands for O, 1 stands for X, and 0 stands for empty
    int board[3][3] = {};
    int winnder = 0;  // winder is 1 of -1 of 9 if draw
    int step = 0;     // number of moves made
    char turn = 'A';  // X or O

   public:
    void make_move(const Move &move);
    int get_winner();
    bool is_empty();
    void set_turn(const Move &move);
    int get_turn();
};
#endif
