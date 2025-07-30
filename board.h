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
    void move_check(std::string input, bool white_move);
    int get_index(char letter, char number);
    int get_col(char letter);
    int get_row(char number);
    void King_handling(std::string input, bool white_move);
    bool check_k_index(int targ_index, int K_pos);
    void Queen_handling(std::string input, bool white_move);
    bool check_q_index(int targ_index, int Q_pos);
    void Rook_handling(std::string input, bool white_move);
    void Bishop_handling(std::string input, bool white_move);
    void Knight_handling(std::string input, bool white_move);
    void pawn_handling(std::string input, bool white_move);




//private:
    std::array<std::unique_ptr<Square>, 64> board;

    bool has_moved;

    int King_w_pos;
    int King_b_pos;

    int Queen_w_pos;
    int Queen_b_pos;

};

#endif
