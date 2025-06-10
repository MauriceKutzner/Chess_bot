#include <iostream>

using namespace std;

enum Piece_type_p {King, Queen, Rook, Bishop, Knight, Pawn, Empty};

class Piece{
  public:
    int position;   //this refers to the index of the square
    bool color;     //think about making this a bool
    bool has_moved;
    int type;
};


class Pawn: public Piece{
  public:
    Pawn(){
      type = 5;
      has_moved = false;
    }

    bool is_legal(int index, int target, bool col){
      if(color ==false){            //if the pawn is black
      
        if (has_moved == false){    //if it has not moved
          
        }
      }
    }

    
};