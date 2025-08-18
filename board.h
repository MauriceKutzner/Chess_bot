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
#include <cstdlib>

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
    void remove_piece_index(int type, int index, bool white_move);

    void King_handling(std::string input, bool white_move);
    void Queen_handling(std::string input, bool white_move);
    void Rook_handling(std::string input, bool white_move);
    void Bishop_handling(std::string input, bool white_move);
    void Knight_handling(std::string input, bool white_move);
    void pawn_handling(std::string input, bool white_move);
    void Castles_handling(std::string input, bool white_move);

    bool check_k_index(int targ_index, int K_pos);
    bool check_q_index(int targ_index, int Q_pos);
    bool check_r_index(int targ_index, int R_pos);
    bool check_b_index(int targ_index, int B_pos);
    bool check_n_index(int targ_index, int N_pos);  
    bool check_p_index(int to, int from, bool is_capture, bool white_move);


    bool is_valid_king_move(int from, int to, bool is_capture, bool white_move);
    bool is_valid_Queen_move(int from, int to, bool is_capture, bool white_move);
    bool is_valid_rook_move(int from, int to, bool is_capture, bool white_move);
    bool is_valid_bishop_move(int from, int to, bool is_capture, bool white_move);
    bool is_valid_knight_move(int from, int to, bool is_capture, bool white_move);
    bool is_valid_pawn_move(int from, int to, bool is_capture, bool white_move);
    bool is_valid_promotion(int from, int to, bool is_capture, bool white_move);
    bool is_valid_en_passent(int from, int to, bool is_capture, bool white_move);
    bool is_valid_castling(std::string input, bool white_move);


    std::vector<int>& get_rook_list(bool white_move);
    std::vector<int>& get_bishop_list(bool white_move);
    std::vector<int>& get_knight_list(bool white_move);
    std::vector<int>& get_queen_list(bool white_move);
    std::vector<int>& get_pawn_list(bool white_move);

    std::vector<int> white_rooks;
    std::vector<int> white_queens;
    std::vector<int> white_bishops;
    std::vector<int> white_knights;
    std::vector<int> white_pawns;

    std::vector<int> black_rooks;
    std::vector<int> black_queens;
    std::vector<int> black_bishops;
    std::vector<int> black_knights;
    std::vector<int> black_pawns;

    std::array<std::unique_ptr<Square>, 64> board;

    bool has_moved;

    int King_w_pos;
    int King_b_pos;

};

#endif
