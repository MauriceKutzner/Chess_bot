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

    struct UndoState{
       

        std::unique_ptr<Piece> captured_piece; // piece that was on the 'to' square before move (nullptr if empty)
        
        bool prev_has_moved = false;        // whether the moving piece had moved before
        bool prev_just_moved_two = false;   // previous state of the just_moved_two flag for pawns

        int prev_king_w_pos, prev_king_b_pos; // previous king positions

        // Positions of pieces before move
        
        std::vector<int> prev_white_rooks;
        std::vector<int> prev_black_rooks;
        std::vector<int> prev_white_pawns;
        std::vector<int> prev_black_pawns;
        std::vector<int> prev_white_bishops;
        std::vector<int> prev_black_bishops;
        std::vector<int> prev_white_knights;
        std::vector<int> prev_black_knights;
        std::vector<int> prev_white_queens;
        std::vector<int> prev_black_queens;

        // Castling info
        bool is_castle = false;
        int rook_from = -1;          // if castling, original rook square
        int rook_to = -1;            // if castling, destination rook square
        bool rook_prev_has_moved = false;
        // Promotion info
        bool is_promotion = false;
        int promoted_piece_type = -1; // 0=Q,1=R,2=B,3=N

        // En passant info
        bool is_en_passant = false;
    };


    
    struct Move{
        std::vector<int> prev_moved_vector;
        std::vector<int> prev_captured_vector;

        int from;
        int to;
        int promotion_type = -1; //-1 means no promotion
        bool is_capture = 0;
        bool is_castle = 0;
        bool is_en_passant = 0;
        bool is_valid = 0;
    };
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
    bool is_on_board(int row, int col);
    int rc_to_index(int row, int col);
    void remove_piece_index(int type, int index, bool white_move);
    void add_piece_index(int type, int index, bool white_move);
    UndoState make_move(const Move& move, bool white_move);
    void unmake_move(Move& move, UndoState& undo, bool white_move);
    bool check_for_checks(bool white_move);
    bool check_for_checkmate(bool white_move);
    vector<Move> find_moves (bool white_move);

    
    Board::Move King_handling(std::string input, bool white_move);
    Board::Move Queen_handling(std::string input, bool white_move);
    Board::Move Rook_handling(std::string input, bool white_move);
    Board::Move Bishop_handling(std::string input, bool white_move);
    Board::Move Knight_handling(std::string input, bool white_move);
    Board::Move pawn_handling(std::string input, bool white_move);
    Board::Move Castles_handling(bool length, bool white_move);

    bool check_k_index(int targ_index, int K_pos);
    bool check_q_index(int targ_index, int Q_pos);
    bool check_r_index(int targ_index, int R_pos);
    bool check_b_index(int targ_index, int B_pos);
    bool check_n_index(int targ_index, int N_pos);  
    bool check_p_index(int to, int from, bool is_capture, bool white_move);
    bool check_en_passant(int to, int from, bool white_move);


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
