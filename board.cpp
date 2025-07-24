#include <iostream>
#include <array>
#include "board.h"
#include "square.h"
#include <memory>
#include "pieces.h"
#include <string>
#include <cctype>

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
      board[4]->set_piece(std::make_unique<King>(true));
      board[60]->set_piece(std::make_unique<King>(false));

      board[3]->set_piece(std::make_unique<Queen>(true));
      board[59]->set_piece(std::make_unique<Queen>(false));

      board[0]->set_piece(std::make_unique<Rook>(true));
      board[7]->set_piece(std::make_unique<Rook>(true));
      board[56]->set_piece(std::make_unique<Rook>(false));
      board[63]->set_piece(std::make_unique<Rook>(false));

      board[2]->set_piece(std::make_unique<Bishop>(true));
      board[5]->set_piece(std::make_unique<Bishop>(true));
      board[58]->set_piece(std::make_unique<Bishop>(false));
      board[61]->set_piece(std::make_unique<Bishop>(false));

      board[1]->set_piece(std::make_unique<Knight>(true));
      board[6]->set_piece(std::make_unique<Knight>(true));
      board[57]->set_piece(std::make_unique<Knight>(false));
      board[62]->set_piece(std::make_unique<Knight>(false));

      for(int i = 8;  i<16; i++){
        board[i]->set_piece(std::make_unique<Pawn>(true));
      }

      for(int i = 48;  i<56; i++){
        board[i]->set_piece(std::make_unique<Pawn>(false));
      }


      
    }

    //void switch_board(){}

    void Board::print_board(){  
      std::cout << endl << "    A   B   C   D   E   F   G   H "<< endl << "  ---------------------------------" << endl << 1;
      for(int i = 0 ; i<64; i++){
        
        if((i%8 == 0) && i != 0){
          std::cout << " |";
          std::cout << endl << "  ---------------------------------" << endl << (i/8+1);
        }
          if (board[i]->get_piece()){
            std::cout << " | " << return_piece_letter(return_p_type(board[i]->get_piece()));
          } 
          else{
            std::cout << " |  ";
          }
      }
      std::cout << " |";
          std::cout << endl << "  ---------------------------------" << endl<< endl;
      
    }

    bool Board::move_check(string input, bool white_move){

      for(int i = 0; i<64; i++){
        if(input[0]== 'o' || input[0] == '0' || input[0] == 'O'){     //special case for castles

        }

        else if(isupper(input[0]) == false){      //if the first letter is not capitalized, it is a pawn move
          
        }

        else{       //for all the other pieces
          for(int i = 0; i<64; i++){
            Piece * piece = board[i]->get_piece().get();
            if(return_piece_letter(return_p_type(board[i]->get_piece())) == input[0]){    //does the piece type match the on specified
              if(board[i]->get_piece()->color == white_move){           //does the color of the piece match that of the player 
                
              }
            }
          }
        }

      }
    }


    void Board::play_game(){
      string input;
      bool is_legal;
      bool white_move = true;       //this tells the program who is to move
      while(1){
        print_board();

        cin >> input;
        if(input == "exit"){
          cout << endl << endl;
          break;
        }

        is_legal = move_check(input, white_move);

        white_move = !white_move;     //for the next turn, the other player has his turn
      }
    }
    


    Square::Square():sq_index(), sq_color(){
    }

    Square::Square(int index, bool color): sq_index(index), sq_color(color), piece(nullptr){        //construct the square with a given color and index
    }

    void Square::set_piece(std::unique_ptr<Piece> new_piece){   //change the piece on the square
        piece = std::move(new_piece);
    }

    std::unique_ptr<Piece>& Square::get_piece(){     //this gets the piece located on the square
        return piece;   //this returns a raw pointer to piece
    }

    int Board::return_p_type(std::unique_ptr<Piece>& piece){
    return piece->type;
  }

    char Board::return_piece_letter(int p_type){
      switch(p_type){
        case 0:
          return 'K';
        case 1:
          return 'Q';
        case 2:
          return 'R';
        case 3:
          return 'B';
        case 4:
          return 'N';
        case 5:
          return 'P';
        default:
          return ' ';
      }
    }
  
    bool Square::return_sq_color(){
      return sq_color;
    }

    bool Square::return_is_empty(){
      return is_empty;
    }
  
    int Square::return_sq_index(){
      return Square::sq_index;
    }

    


  
    

int main(){
  Board B;

  B.play_game();

  //Piece * test_piece = board[10]->get_piece();
  
  
  
  return 0;
}