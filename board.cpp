#include <iostream>
#include <array>
#include "board.h"
#include "square.h"
#include <memory>

using namespace std;

 
    
    Board::Board(){
      fill_board();
    }

    void Board::fill_board(){
      
      for(int n = 0; n<64; n += 2){
        board[n] = std::make_unique<Square>(n, false);    //declare all black squares 
      }
      for(int n = 1; n<64; n += 2){
        board[n] = std::make_unique<Square>(n, true);     //declare all white squares 
      }

      for(int n = 8; n< 16; n++){
        board[n]->make_pawn();
      }
      for(int n = 48; n< 56; n++){
        board[n]->make_pawn();
      }
      for(int n = 16; n<48; n++){
        board[n]->make_empty();
      }
      {       //this initializes all the other pieces
        board[0]->make_rook(); 
        board[7]->make_rook(); 
        board[56]->make_rook(); 
        board[63]->make_rook(); 
        board[4]->make_king(); 
        board[60]->make_king(); 
        board[3]->make_queen(); 
        board[59]->make_queen(); 
        board[2]->make_knight();
        board[5]->make_knight();
        board[57]->make_knight();
        board[62]->make_knight(); 
        board[1]->make_bishop();
        board[6]->make_bishop();
        board[58]->make_bishop();
        board[61]->make_bishop();
      }
     
    }

    //void switch_board(){}

    void Board::print_board(){
      std::cout << " ---------------------------------" << endl;
      for(int i = 0 ; i<64; i++){
        
        if((i%8 == 0) && i != 0){
          std::cout << " |";
          std::cout << endl << " ---------------------------------" << endl;
        }
        std::cout << " | " << piece_to_char(board[i]->return_type());
      }
      std::cout << " |";
          std::cout << endl << " ---------------------------------" << endl;
    }

    char Board::piece_to_char(Piece_type p){
      switch(p){
        case King:
          return 'K';
        case Queen:
          return 'Q';
        case Rook:
          return 'R';
        case Bishop:
          return 'B';
        case Knight:
          return 'H';
        case Pawn:
          return 'P';
        case Empty:
          return '0';
        default:
          return '?';
      }
    }
    





    Square::Square():sq_index(), sq_color(){

    }

    Square::Square(int index, bool color): sq_index(index), sq_color(color){        //construct the square with a given color and index

    }
    void Square::make_pawn(){
      type = Pawn;
    }
    void Square::make_king(){
      type = King;
    }
    void Square::make_knight(){
      type = Knight;
    }
    void Square::make_bishop(){
      type = Bishop;
    }
    void Square::make_rook(){
      type = Rook;
    }
    void Square::make_queen(){
      type = Queen;
    }
    void Square::make_empty(){
      type = Empty;
    }
    
  
    bool Square::return_sq_color(){
      return sq_color;
    }

    void Square::set_sq_color(bool col){
      if(col == false){
        sq_color = false;
      }
    }
    bool Square::return_is_empty(){
      return is_empty;
    }
  
    int Square::return_sq_index(){
      return Square::sq_index;
    }

    Piece_type Square::return_type(){
      return Square::type;
    }



  
    

int main(){
  Board B;

  B.print_board();
  
  
  
  return 0;
}