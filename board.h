#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <memory>
#include <iostream>
#include "square.h"
#include "pieces.h"

class Square;  //Forward declaration


class Board {
public:

    Board();
    void fill_board();
    void print_board();
    char piece_to_char(Piece_type p);

private:
    std::array<std::unique_ptr<Square>, 64> board;
};

#endif
