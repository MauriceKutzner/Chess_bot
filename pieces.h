#ifndef PIECES_H
#define PIECES_H

//#include "square.h"
//#include "board.h"

class Piece{
  public:
    int position;   //this refers to the index of the square
    const bool color;     //think about making this a bool
    bool has_moved;
    int type;

    Piece(int pos, bool pcol, bool h_mov, int tp) : position(pos), color(pcol), has_moved(h_mov), type(tp){
    };

    int get_index(char * target);

    

    //virtual void move_pc(char * target);

    virtual ~Piece();
    
};

class Pawn: public Piece{
  public:
    Pawn(bool pcolor);
    bool just_moved_two = false;
};

class King: public Piece{
  public:
    King(bool pcolor);
};

class Queen: public Piece{
  public:
    Queen(bool pcolor);
};

class Rook: public Piece{
  public:
    Rook(bool pcolor);
};

class Bishop: public Piece{
  public:
    Bishop(bool pcolor);
};

class Knight: public Piece{
  public:
    Knight(bool pcolor);
};

#endif
