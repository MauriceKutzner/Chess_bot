#ifndef PIECES_H
#define PIECES_H

#include "square.h"
#include "board.h"

class Piece{
  public:
    int position;   //this refers to the index of the square
    bool color;     //think about making this a bool
    bool has_moved;
    int type;

    virtual void move_pc(char * target);

    virtual ~Piece();
};

class Pawn: public Piece{
  Pawn();
  void move_pc(char * target) override;
};

class King: public Piece{
  King();
  void move_pc(char * target) override;
};

class Queen: public Piece{
  Queen();
  void move_pc(char * target) override;
};

class Rook: public Piece{
  Rook();
  void move_pc(char * target) override;
};

class Bishop: public Piece{
  Bishop();
  void move_pc(char * target) override;
};

class Knight: public Piece{
  Knight();
  void move_pc(char * target) override;
};

#endif
