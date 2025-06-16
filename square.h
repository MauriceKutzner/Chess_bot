#ifndef SQUARE_H
#define SQUARE_H

class Board;    //Forward declare Board
class Piece;    //Forward declare Piece
enum Piece_type {King, Queen, Rook, Bishop, Knight, Pawn, Empty};

class Square {
public:
    Square();
    Square(int index, bool color);

    void make_pawn();
    void make_king();
    void make_knight();
    void make_bishop();
    void make_rook();
    void make_queen();
    void make_empty();

    bool return_sq_color();
    void set_sq_color(bool col);
    bool return_is_empty();
    int return_sq_index();
    
    Piece_type return_type();


    int sq_index;
    bool sq_color;
    bool is_empty;
    Piece_type type;
};

#endif