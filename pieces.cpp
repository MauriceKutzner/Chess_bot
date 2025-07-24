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

  
/*
  void Piece::move_pc(char * target){
    int target_square = get_index(target);


  }
*/
  

  Piece::~Piece(){

  }

  
  King::King(bool pcolor):
    Piece(0, pcolor, false,0){};
  
  //void King::move_pc(char * target){

 // }

  Queen::Queen(bool pcolor):
    Piece(0, pcolor, false,1){};

  //void Queen::move_pc(char * target){

  //}

  Rook::Rook(bool pcolor):
    Piece(0, pcolor, false,2){};

  //void Rook::move_pc(char * target){

  //}

  Bishop::Bishop(bool pcolor):
    Piece(0, pcolor, false,3){};

  /*void Bishop::move_pc(char * target){

  }*/

  Knight::Knight(bool pcolor):
    Piece(0, pcolor, false,4){};

  /*void Knight::move_pc(char * target){

  }*/

  Pawn::Pawn(bool pcolor):
    Piece(0, pcolor, false,5){};

  /*void Pawn::move_pc(char * target){

  }*/


