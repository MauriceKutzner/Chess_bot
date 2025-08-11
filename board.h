#ifndef BOARD_H
#define BOARD_H

#include <array>
#include <memory>
#include <iostream>
#include "square.h"
#include "pieces.h"
#include <string>
#include <cctype>
#include <vector>

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
    int index_to_row(int index);
    int index_to_col(int index);

    void King_handling(std::string input, bool white_move);
    bool check_k_index(int targ_index, int K_pos);
    void Queen_handling(std::string input, bool white_move);
    bool check_q_index(int targ_index, int Q_pos);
    void Rook_handling(std::string input, bool white_move);

    bool is_valid_rook_move(int from, int to, bool is_capture, bool white_move);
    bool is_valid_bishop_move(int from, int to, bool is_capture, bool white_move);
    bool is_valid_knight_move(int from, int to, bool is_capture, bool white_move);

    std::vector<int>& get_rook_list(bool white_move);
    std::vector<int>& get_bishop_list(bool white_move);
    std::vector<int>& get_knight_list(bool white_move);

    bool check_r_index(int targ_index, int R_pos);
    void Bishop_handling(std::string input, bool white_move);
    bool check_b_index(int targ_index, int B_pos);
    void Knight_handling(std::string input, bool white_move);
    bool check_n_index(int targ_index, int N_pos);
    void pawn_handling(std::string input, bool white_move);



//private:
    std::vector<int> white_rooks;
    std::vector<int> white_queens;
    std::vector<int> white_bishops;
    std::vector<int> white_knights;


    std::vector<int> black_rooks;
    std::vector<int> black_queens;
    std::vector<int> black_bishops;
    std::vector<int> black_knights;
    std::array<std::unique_ptr<Square>, 64> board;

    bool has_moved;

    int King_w_pos;
    int King_b_pos;

    int Queen_w_pos;
    int Queen_b_pos;

};

#endif
