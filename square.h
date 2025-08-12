#ifndef SQUARE_H
#define SQUARE_H

class Board;    //Forward declare Board
class Piece;    //Forward declare Piece

class Square {
public:
    Square();
    Square(int index, bool color);
/*
    void make_pawn();
    void make_king();
    void make_knight();
    void make_bishop();
    void make_rook();
    void make_queen();
    void make_empty();
*/
    void set_sq_color(bool col);
    void set_piece(std::unique_ptr<Piece> newPiece);
    std::unique_ptr<Piece>& get_piece();
    
    


    

    int sq_index;
    bool sq_color;
    bool is_empty;
    
    std::unique_ptr<Piece> piece;


};

#endif