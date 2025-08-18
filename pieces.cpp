#include <iostream>
#include "pieces.h"
#include "board.h"
#include "square.h"

using namespace std;


  int Piece::get_index(char * target){
    int col =  1 + (target[0] -'a');
    int row = (target[1] -'0');

    int index = (((row-1)*8)+(col -1));   //get the 0 based square index
    return index;
  }
  

  Piece::~Piece(){

  }

  
  King::King(bool pcolor):
    Piece(0, pcolor, false,0){};
  

  Queen::Queen(bool pcolor):
    Piece(0, pcolor, false,1){};


  Rook::Rook(bool pcolor):
    Piece(0, pcolor, false,2){};


  Bishop::Bishop(bool pcolor):
    Piece(0, pcolor, false,3){};

  
  Knight::Knight(bool pcolor):
    Piece(0, pcolor, false,4){};


  Pawn::Pawn(bool pcolor):
    Piece(0, pcolor, false,5), just_moved_two(false){};