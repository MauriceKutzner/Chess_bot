#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <memory>
#include <iostream>
#include "square.h"
#include "pieces.h"
#include <string>
#include <cctype>

class Square;  //Forward declaration
class Piece;


class Board {
public:
    char return_piece_letter(int p_type);
    Board();
    void fill_board();
    void print_board();
    int return_p_type(std::unique_ptr<Piece>& piece);
    void play_game();
    bool move_check(string input, bool white_move);
    int get_index(char letter, char number);
    void King_handling(string input);
    void Queen_handling(string input);
    void Rook_handling(string input);
    void Bishop_handling(string input);
    void Knight_handling(string input);
    void pawn_handling(string input, bool white_move);




//private:
    std::array<std::unique_ptr<Square>, 64> board;
};

#endif
