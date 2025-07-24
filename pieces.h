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
    //void move_pc(char * target) override;
};

class King: public Piece{
  public:
    King(bool pcolor);
    //void move_pc(char * target) override;
};

class Queen: public Piece{
  public:
    Queen(bool pcolor);
    //void move_pc(char * target) override;
};

class Rook: public Piece{
  public:
    Rook(bool pcolor);
    //void move_pc(char * target) override;
};

class Bishop: public Piece{
  public:
    Bishop(bool pcolor);
    //void move_pc(char * target) override;
};

class Knight: public Piece{
  public:
    Knight(bool pcolor);
    //void move_pc(char * target) override;
};

#endif
