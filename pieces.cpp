#include <iostream>
#include "pieces.h"
#include "board.h"
#include "square.h"

using namespace std;

  enum Piece_type_p {King, Queen, Rook, Bishop, Knight, Pawn, Empty};

  int Piece::get_index(char * target){
    int col =  1 + (target[0] -'a');
    int row = (target[1] -'0');

    int index = (((row-1)*8)+(col -1));   //get the 0 based square index
    return index;
  }

  void Piece::move_pc(char * target){
    int target_square = get_index(target);
    

  }
  Piece::~Piece(){

  }

  Pawn::Pawn(){
    type = 5;
    has_moved = false;
  }

  King::King(){
    type = 0;
    has_moved = false;
  }

  Queen::Queen(){
    type = 1;
    has_moved = false;
  }

  Rook::Rook(){
    type = 2;
    has_moved = false;
  }

  Bishop::Bishop(){
    type = 3;
    has_moved = false;
  }

  Knight::Knight(){
    type = 4;
    has_moved = false;
  }

