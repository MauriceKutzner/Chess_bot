#include <iostream>
#include <array>
#include "board.h"

using namespace std;
class Board{
  public:

    enum Piece {King, Queen, Rook, Bishop, Knight, Pawn, bKing, bQueen, bRook, bBishop, bKnight, bPawn,Empty};
    Board(){
      fill_board();
    }

    void fill_board(){
      for(int n = 0; n < 64 ;n++){
        if(n == 0 || n == 7 ){
          board[n] = Rook;
        }

        else if (n == 63|| n == 56){
          board[n] = bRook;
        }

        else if(n == 2 || n == 5){
          board[n] = Bishop;
        }

        else if(n == 61 || n == 58){
          board[n] = bBishop;
        }

        else if(n == 1 || n == 6){
          board[n] = Knight;
        }

        else if(n == 62 || n == 57){
          board[n] = bKnight;
        }

        else if(n == 3){
          board[n] = Queen;
        }
        else if(n == 4){
          board[n] = King;
        }
         else if(n == 59){
          board[n] = bQueen;
        }
        else if(n == 60){
          board[n] = bKing;
        }
        else if (n  > 7 && n < 16){
          board[n] = Pawn;
        }
        else if (n > 47 && n < 56){
          board[n] = bPawn;
        }
        else{
          board[n] = Empty;
        }

      }
    }

    //void switch_board(){}

    void print_board(){
      std::cout << " ---------------------------------" << endl;
      for(int i = 0 ; i<64; i++){
        
        if((i%8 == 0) && i != 0){
          std::cout << " |";
          std::cout << endl << " ---------------------------------" << endl;
        }
        std::cout << " | " << piece_to_char(board[i]);
      }
      std::cout << " |";
          std::cout << endl << " ---------------------------------" << endl;
    }

    char piece_to_char(Piece p){
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
        case bKing:
          return 'k';
        case bQueen:
          return 'q';
        case bRook:
          return 'r';
        case bBishop:
          return 'b';
        case bKnight:
          return 'h';
        case bPawn:
          return 'p';
        case Empty:
          return '0';
        default:
          return '?';
      }
    }
    
    std::array<Piece, 64> board;

};

int main(){
  Board B;

  B.print_board();
  
  
  
  return 0;
}