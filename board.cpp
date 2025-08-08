#include <iostream>
#include <array>
#include "board.h"
#include "square.h"
#include <memory>
#include "pieces.h"
#include <string>
#include <cctype>
#include <vector>

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
      King_w_pos = 4;
      board[60]->set_piece(std::make_unique<King>(false));
      King_b_pos = 60;

      board[3]->set_piece(std::make_unique<Queen>(true));
      white_queens = {3};
      board[59]->set_piece(std::make_unique<Queen>(false));
      black_queens = {59};

      board[0]->set_piece(std::make_unique<Rook>(true));
      board[7]->set_piece(std::make_unique<Rook>(true));
      white_rooks  = {0, 7};
      board[56]->set_piece(std::make_unique<Rook>(false));
      board[63]->set_piece(std::make_unique<Rook>(false));
      black_rooks = {56, 63};

      board[2]->set_piece(std::make_unique<Bishop>(true));
      board[5]->set_piece(std::make_unique<Bishop>(true));
      white_bishops = {2, 5};
      board[58]->set_piece(std::make_unique<Bishop>(false));
      board[61]->set_piece(std::make_unique<Bishop>(false));
      black_bishops = {58, 61};

      board[1]->set_piece(std::make_unique<Knight>(true));
      board[6]->set_piece(std::make_unique<Knight>(true));
      white_knights = {1, 6};
      board[57]->set_piece(std::make_unique<Knight>(false));
      board[62]->set_piece(std::make_unique<Knight>(false));
      black_knights = {57, 62};

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
            if(board[i]->get_piece()->color == true){
              std::cout << " | " << return_piece_letter(return_p_type(board[i]->get_piece()));
            }
            else{
              std::cout << " | " << char(tolower(return_piece_letter(return_p_type(board[i]->get_piece()))));

            }
          } 
          else{
            std::cout << " |  ";
          }
      }
      std::cout << " |";
          std::cout << endl << "  ---------------------------------" << endl<< endl;
      
    }

    void Board::move_check(std::string input, bool white_move){

      
      if(input[0]== 'o' || input[0] == '0' || input[0] == 'O'){     //special case for castles
      }
      
      else  if(isupper(input[0]) == false){      //if the first letter is not capitalized, it is a pawn move
             
        pawn_handling(input, white_move);
        return;
      }

      else switch(input[0]){
        case 'K':
          King_handling(input, white_move);
          return;
        case 'Q':
          Queen_handling(input, white_move);
          return;
        case 'R':
          Rook_handling(input, white_move);
          return;
        case 'B':
          Bishop_handling(input, white_move);
          return;
        case 'N':
          Knight_handling(input, white_move);
          return;
      }
    }

    void Board::pawn_handling(std::string input, bool white_move){  //include en passent
      if (input[1] == 'x'){     //case for a pawn capturing a piece
        int index = get_index(input[2], input[3]);
        int col_def = get_col(input[2]);
        int col_att = get_col(input[0]);

        if(white_move == true){   //for white pawns

          if(col_def > col_att){

            if(index - 9 >= 0 && board[index - 9]->get_piece() && 
              board[index - 9]-> get_piece()->type == 5 && 
              board[index - 9]->get_piece()->color == true){

              std::unique_ptr<Piece>& piece = board[index - 9]->get_piece();    //select pawn as piece
              board[index]->set_piece(nullptr);   //delete piece = captured
              board[index]->set_piece(std::move(piece));    //replace with pawn
              has_moved = true;
              return;
            }
          }

          if(col_def < col_att){

            if(index - 7 >=0 && board[index - 7]->get_piece() 
              && board[index - 7]-> get_piece()->type == 5 && board[index - 7]->get_piece()->color == true){

              std::unique_ptr<Piece>& piece = board[index - 7]->get_piece();
              board[index]->set_piece(nullptr);
              board[index]->set_piece(std::move(piece));
              has_moved = true;
              return;
            }
          }
          else{
            return;
          }
        }

        if(white_move == false){    //for black pawns

          if(col_def > col_att){
            if(index + 7 >= 0 && board[index + 7]->get_piece() && 
              board[index + 7]-> get_piece()->type == 5 && 
              board[index + 7]->get_piece()->color == false){

              std::unique_ptr<Piece>& piece = board[index + 7]->get_piece();
              board[index]->set_piece(nullptr);
              board[index]->set_piece(std::move(piece));
              has_moved = true;
              return;
            }
          }
          if(col_def < col_att){
            if(index +9 >=0 && board[index +9]->get_piece() 
              && board[index +9]-> get_piece()->type == 5 && board[index + 9]->get_piece()->color == false){

              std::unique_ptr<Piece>& piece = board[index + 9]->get_piece();
              board[index]->set_piece(nullptr);
              board[index]->set_piece(std::move(piece));
              has_moved = true;
              return;
            }
          }
          else{
            return;
          }
          
        }
        else{
          return;
        }
      }
      else{     //for non-capture pawn moves
        if (white_move){
          int index = get_index(input[0], input[1]);

          // Single move forward
          if (index - 8 >= 0 && board[index - 8]->get_piece() &&
            board[index - 8]->get_piece()->type == 5 &&
            board[index]->get_piece() == nullptr &&
            board[index - 8]->get_piece()->color == true){

            std::unique_ptr<Piece>& piece = board[index - 8]->get_piece();
            board[index]->set_piece(std::move(piece));
            has_moved = true;
            return;
          }

          // Double move from starting rank
          if(get_row(input[1]) == 4 &&      //pawn has to be on starting row
            index - 16 >= 0 && 
            board[index - 8]->get_piece() == nullptr &&
            board[index - 16]->get_piece() &&
            board[index - 16]->get_piece()->type == 5 &&
            board[index]->get_piece() == nullptr &&
            board[index - 16]->get_piece()->color == true) {

            std::unique_ptr<Piece>& piece = board[index - 16]->get_piece();
            board[index]->set_piece(std::move(piece));
            has_moved = true;
            return;
          }
          else{
            return;
          }
        }
        if(white_move == false){      //for a black  pawn
          int index = get_index(input[0], input[1]);

          // Single move forward
          if (index + 8 >= 0 && board[index + 8]->get_piece() &&
            board[index + 8]->get_piece()->type == 5 &&
            board[index]->get_piece() == nullptr && 
            board[index + 8]->get_piece()->color == false){

            std::unique_ptr<Piece>& piece = board[index + 8]->get_piece();
            board[index]->set_piece(std::move(piece));
            has_moved = true;
            return;
          }

            // Double move from starting rank
          if(get_row(input[1]) == 5 &&
            index + 16 >= 0 && 
            board[index + 8]->get_piece() == nullptr &&
            board[index + 16]->get_piece() &&
            board[index + 16]->get_piece()->type == 5 &&
            board[index]->get_piece() == nullptr && 
            board[index + 16]->get_piece()->color == false){

            std::unique_ptr<Piece>& piece = board[index + 16]->get_piece();
            board[index]->set_piece(std::move(piece));
            has_moved = true;
            return;
          }
          else{
            return;
          }
        }
      }
    }

    void Board::King_handling(std::string input, bool white_move){
      if(input[1] == 'x'){    //King captures piece
        int index = get_index(input[2], input[3]);
        if(white_move == true &&
          board[King_w_pos]->get_piece() &&
          board[index]->get_piece() &&
          board[King_w_pos]->get_piece()->type == 0 && 
          check_k_index(index, King_w_pos) == true){
          
          board[index]->set_piece(nullptr);
          board[index]->set_piece(move(board[King_w_pos]->get_piece()));
          King_w_pos = index;
          has_moved = true;
          return;
        }
        else if(white_move == false &&
          board[King_b_pos]->get_piece() &&
          board[index]->get_piece() &&
          board[King_b_pos]->get_piece()->type == 0 && 
          check_k_index(index, King_b_pos) == true){
          
          board[index]->set_piece(nullptr);
          board[index]->set_piece(move(board[King_b_pos]->get_piece()));
          King_b_pos = index;
          has_moved = true;
          return;
        }
        else{
          return;
        }
      }
      else{   //normal King move
        int index = get_index(input[1], input[2]);
        if(white_move == true &&
          board[King_w_pos]->get_piece() &&
          !board[index]->get_piece() &&
          board[King_w_pos]->get_piece()->type == 0 && 
          check_k_index(index, King_w_pos) == true){
          
          board[index]->set_piece(move(board[King_w_pos]->get_piece()));
          King_w_pos = index;
          has_moved = true;
          return;
        }
        else if(white_move == false &&
          board[King_b_pos]->get_piece() &&
          !board[index]->get_piece() &&
          board[King_b_pos]->get_piece()->type == 0 && 
          check_k_index(index, King_b_pos) == true){
          
          board[index]->set_piece(move(board[King_b_pos]->get_piece()));
          King_b_pos = index;
          has_moved = true;
          return;
        }
        else{
          return;
        }
      }
    }

    void Board::Queen_handling(std::string input, bool white_move){
      if(input[1] == 'x'){    //queen captures piece
        int index = get_index(input[2], input[3]);
        if(white_move == true &&
          board[Queen_w_pos]->get_piece() &&
          board[index]->get_piece() &&
          board[Queen_w_pos]->get_piece()->type == 1 && 
          check_q_index(index, Queen_w_pos) == true){
          
          board[index]->set_piece(nullptr);
          board[index]->set_piece(move(board[Queen_w_pos]->get_piece()));
          Queen_w_pos = index;
          has_moved = true;
          return;
        }
        else if(white_move == false &&
          board[Queen_b_pos]->get_piece() &&
          board[index]->get_piece() &&
          board[Queen_b_pos]->get_piece()->type == 1 && 
          check_q_index(index, Queen_b_pos) == true){
          
          board[index]->set_piece(nullptr);
          board[index]->set_piece(move(board[Queen_b_pos]->get_piece()));
          Queen_b_pos = index;
          has_moved = true;
          return;
        }
        else{
          return;
        }
      }
      else{   //normal King move
        int index = get_index(input[1], input[2]);
        if(white_move == true &&
          board[Queen_w_pos]->get_piece() &&
          !board[index]->get_piece() &&
          board[Queen_w_pos]->get_piece()->type == 1 && 
          check_q_index(index, Queen_w_pos) == true){
          
          board[index]->set_piece(move(board[Queen_w_pos]->get_piece()));
          Queen_w_pos = index;
          has_moved = true;
          return;
        }
        else if(white_move == false &&
          board[Queen_b_pos]->get_piece() &&
          !board[index]->get_piece() &&
          board[Queen_b_pos]->get_piece()->type == 1 && 
          check_q_index(index, Queen_b_pos) == true){
          
          board[index]->set_piece(move(board[Queen_b_pos]->get_piece()));
          Queen_b_pos = index;
          has_moved = true;
          return;
        }
        else{
          return;
        }
      }
    }

    void Board::Rook_handling(std::string input, bool white_move){
      if(input[1]== 'x' || input[2] == 'x'){      //Rook captures a piece
        
        if(input.length() > 4){   //case for Rdxd5

          /*White Turn*/

          if(white_move == true){
            if(('1' <= input[1] && input[1] <= '8') || ('a' <= input[1] && input[1]<= 'h')){   //case for moves like R1d7
              int index = get_index(input[3], input[4]);
              int targ_row = get_row(input[3]);
              int targ_col = get_col(input[4]);
              auto& rooks = get_rook_list(white_move);
              for(int& i : rooks){

                if(isdigit(input[1])){          //check which rook has to be selected based on given row
                  int disamb_row = get_row(input[1]);
                  if (index_to_row(i) != disamb_row){
                    continue;
                  }
                }

                else if(isalpha(input[1])){     //check which rook has to be selected based on given column
                  int disamb_col = get_col(input[1]);
                  if (index_to_col(i) != disamb_col){
                    continue;
                  }
                }

                if(index_to_col(i) == targ_col || index_to_row(i) == targ_row){  //target and rook on the same column/row
                  if(is_valid_rook_move(i, index, true)){

                    board[index]->set_piece(nullptr);
                    board[index]->set_piece(move(board[i]->get_piece()));   //set rook to target square
                    i = index;    //update white_rooks
                    has_moved = true;
                    return;
                  }
                }
              }
            }
          }

          /*Black Turn*/

          if(white_move == false){
            if(('1' <= input[1] && input[1] <= '8') || ('a' <= input[1] && input[1]<= 'h')){   //case for moves like R1d7
              int index = get_index(input[3], input[4]);
              int targ_row = get_row(input[3]);
              int targ_col = get_col(input[4]);
              auto& rooks = get_rook_list(white_move);

              for(int& i : rooks){

                if(isdigit(input[1])){          //check which rook has to be selected based on given row
                  int disamb_row = get_row(input[1]);
                  if (index_to_row(i) != disamb_row){
                    continue;
                  }
                }

                else if(isalpha(input[1])){     //check which rook has to be selected based on given column
                  int disamb_col = get_col(input[1]);
                  if (index_to_col(i) != disamb_col){
                    continue;
                  }
                }

                if(index_to_col(i) == targ_col || index_to_row(i) == targ_row){  //target and rook on the same column/row
                  if(is_valid_rook_move(i, index, true)){
                    board[index]->set_piece(nullptr);
                    board[index]->set_piece(move(board[i]->get_piece()));   //set rook to target square
                    i = index;    //update black_rooks
                    has_moved = true;
                    return;
                  }
                }
              }
            }
          }
        }
        else if(input.length() == 4){   //case for Rxd5

          /*White Turn*/

          if(white_move == true){
            int index = get_index(input[2], input[3]);
            int targ_row = get_row(input[2]);
            int targ_col = get_col(input[3]);
            auto& rooks = get_rook_list(white_move);

            for(int& i : rooks){
              if(index_to_col(i) == targ_col || index_to_row(i) == targ_row){  //target and rook on the same column/row
                if(is_valid_rook_move(i, index, true)){
                  board[index]->set_piece(nullptr);
                  board[index]->set_piece(move(board[i]->get_piece()));   //set rook to target square
                  i = index;    //update white_rooks
                  has_moved = true;
                  return;
                }
              }
            }            
          }


          /*Black Turn*/

          else if(white_move == false){
            int index = get_index(input[2], input[3]);
            int targ_row = get_row(input[2]);
            int targ_col = get_col(input[3]);
            auto& rooks = get_rook_list(white_move);

            for(int& i : rooks){
              if(index_to_col(i) == targ_col || index_to_row(i) == targ_row){  //target and rook on the same column/row
                if(is_valid_rook_move(i, index, true)){
                  board[index]->set_piece(nullptr);
                  board[index]->set_piece(move(board[i]->get_piece()));   //set rook to target square
                  i = index;    //update black_rooks
                  has_moved = true;
                  return;
                }
              }
            }  
          }
        }
      }

      else{   //normal rook move

        /*White Turn*/

        if(white_move == true){

          if(input.length()>3){ //case for several rooks being able to move to the same square

            if(('1' <= input[1] && input[1] <= '8') || ('a' <= input[1] && input[1]<= 'h')){   //case for moves like R1d7
              int index = get_index(input[2], input[3]);
              int targ_row = get_row(input[2]);
              int targ_col = get_col(input[3]);
              auto& rooks = get_rook_list(white_move);

              for(int& i : rooks){

                if(isdigit(input[1])){          //check which rook has to be selected based on given row
                  int disamb_row = get_row(input[1]);
                  if (index_to_row(i) != disamb_row){
                    continue;
                  }
                }

                else if(isalpha(input[1])){     //check which rook has to be selected based on given column
                  int disamb_col = get_col(input[1]);
                  if (index_to_col(i) != disamb_col){
                    continue;
                  }
                }

                if(index_to_col(i) == targ_col || index_to_row(i) == targ_row){  //target and rook on the same column/row
                  if(is_valid_rook_move(i, index, false)){
                    
                    board[index]->set_piece(move(board[i]->get_piece()));   //set rook to target square
                    i = index;    //update white_rooks
                    has_moved = true;
                    return;
                  }
                }
              }
            }
          }

          else{     //normal case for rook move
            int index = get_index(input[1], input[2]);
            int targ_row = get_row(input[1]);
            int targ_col = get_col(input[2]);
            auto& rooks = get_rook_list(white_move);

            for(int& i : rooks){
              if(index_to_col(i) == targ_col || index_to_row(i) == targ_row){  //target and rook on the same column/row
                if(is_valid_rook_move(i, index, false)){
                  
                  board[index]->set_piece(move(board[i]->get_piece()));   //set rook to target square
                  i = index;    //update white_rooks
                  has_moved = true;
                  return;
                }
              }
            }
          }
        }

        /*Black Turn*/

        else if(white_move == false){

          if(input.length()>3){ //case for several rooks being able to move to the same square

            if(('1' <= input[1] && input[1] <= '8') || ('a' <= input[1] && input[1]<= 'h')){   //case for moves like R1d7
              int index = get_index(input[2], input[3]);
              int targ_row = get_row(input[2]);
              int targ_col = get_col(input[3]);
              auto& rooks = get_rook_list(white_move);

              for(int& i : rooks){
                if(isdigit(input[1])){          //check which rook has to be selected based on given row
                  int disamb_row = get_row(input[1]);
                  if (index_to_row(i) != disamb_row){
                    continue;
                  }
                }

                else if(isalpha(input[1])){     //check which rook has to be selected based on given column
                  int disamb_col = get_col(input[1]);
                  if (index_to_col(i) != disamb_col){
                    continue;
                  }
                }

                if(index_to_col(i) == targ_col || index_to_row(i) == targ_row){  //target and rook on the same column/row
                  if(is_valid_rook_move(i, index, false)){
                    
                    board[index]->set_piece(move(board[i]->get_piece()));   //set rook to target square
                    i = index;    //update black_rooks
                    has_moved = true;
                    return;
                  }
                }
              }
            }
          }

          else{     //normal case for rook move
            int index = get_index(input[1], input[2]);
            int targ_row = get_row(input[1]);
            int targ_col = get_col(input[2]);
            auto& rooks = get_rook_list(white_move);

            for(int& i : rooks){
              if(index_to_col(i) == targ_col || index_to_row(i) == targ_row){  //target and rook on the same column/row
                if(is_valid_rook_move(i, index, false)){
                  
                  board[index]->set_piece(move(board[i]->get_piece()));   //set rook to target square
                  i = index;    //update black_rooks
                  has_moved = true;
                  return;
                }
              }
            }
          }
        }
      }
    }

    std::vector<int>& Board::get_rook_list(bool white_move){
      return white_move ? white_rooks : black_rooks;
    }

    bool Board::is_valid_rook_move(int from, int to, bool is_capture){

      if(is_capture && 
        board[from]->get_piece() &&
        board[to]->get_piece() && 
        board[from]->get_piece()->type == 2 &&
        check_r_index(to, from) == true){   

        return true;
      }

      else if(!is_capture && 
        board[from]->get_piece() &&
        board[to]->get_piece() == nullptr && 
        board[from]->get_piece()->type == 2 &&
        check_r_index(to, from) == true){
        
        return true;
      }

      else{
        return false;
      }
    }

    void Board::Bishop_handling(std::string input, bool white_move){
      
    }

    void Board::Knight_handling(std::string input, bool white_move){
      
    }

    int Board::index_to_row(int index){
      return (1 + (index / 8));
    }
    int Board::index_to_col(int index){
      return (1 + (index % 8));
    }

    bool Board::check_k_index(int targ_index, int K_pos){
      static const int offsets[8] = {-9, -8, -7, -1, 1, 7, 8, 9};

      int king_row = K_pos / 8;
      int king_col = K_pos % 8;

      for (int offset : offsets){
        int new_pos = K_pos + offset;

        // 1. Check if the new position is within board bounds
        if (new_pos < 0 || new_pos >= 64){
          continue;
        }

        // 2. Calculate the row and column of the new position
        int new_row = new_pos / 8;
        int new_col = new_pos % 8;

        // 3. Ensure move doesn't wrap around (e.g. from H1 to A2)
        if (std::abs(king_row - new_row) <= 1 && std::abs(king_col - new_col) <= 1){
          if (new_pos == targ_index) {
            return true; // The target index is a valid King move
          }
        }
      }
      return false; // Target index is not reachable by the King
    }

    bool Board::check_q_index(int targ_index, int Q_pos) {
      static const int directions[8] = {-9, -8, -7, -1, 1, 7, 8, 9};

      for(int dir : directions){
        int current_pos = Q_pos;

        while(true){
          int next_pos = current_pos + dir;

          // Bounds check
          if(next_pos < 0 || next_pos >= 64){
            break;
          }
          int curr_row = current_pos / 8;
          int next_row = next_pos / 8;

          // Row wrap check for horizontal movement
          if((dir == -1 || dir == 1) && next_row != curr_row){
            break;
          }
          // Row wrap check for diagonal movement (only needed for dirs that aren't purely vertical)
          if((dir == -9 || dir == -7 || dir == 7 || dir == 9) &&
            std::abs((next_pos % 8) - (current_pos % 8)) != 1){

            break;
          }
          current_pos = next_pos;

          if(current_pos == targ_index){
            return true;
          }
          if(board[current_pos]->get_piece()){
            break;
          } 
        }
      }
      return false;
    }


    bool Board::check_r_index(int targ_index, int R_pos) {
      static const int directions[4] = {-8, -1, 1, 8};  // up, left, right, down

      for(int dir : directions){
      int current_pos = R_pos;

        while(true){
          int next_pos = current_pos + dir;

          if(next_pos < 0 || next_pos >= 64){
            break;
          }

          int curr_row = current_pos / 8;
          int next_row = next_pos / 8;

          // Row wrap check for horizontal movement
          if((dir == -1 || dir == 1) && next_row != curr_row){
            break;
          }

          current_pos = next_pos;

          if(current_pos == targ_index){
            return true;
          }

          if(board[current_pos]->get_piece()){
            break;
          }
        }
      }

      return false;
    }

    bool Board::check_b_index(int targ_index, int B_pos){
      static const int directions[4] = {-9, -7, 7, 9};  // diagonal directions

      for(int dir : directions){
        int current_pos = B_pos;

        while(true){
          int next_pos = current_pos + dir;

          if(next_pos < 0 || next_pos >= 64){
            break;
          }

          int curr_col = current_pos % 8;
          int next_col = next_pos % 8;

          // Column wrap check for diagonal movement
          if(std::abs(next_col - curr_col) != 1){
            break;
          }

          current_pos = next_pos;

          if(current_pos == targ_index){
            return true;
          }

          if(board[current_pos]->get_piece()){
            break;
          }
        }
      }

      return false;
    }
    

    int Board::get_index(char letter, char number){
      int col =  1 + (letter -'a');
      int row = (number -'0');

      int index = (((row-1)*8)+(col -1));   //get the 0 based square index
      return index;
    }

    int Board::get_col(char letter){
      int col = 1 + (letter - 'a');
      return col;
    }

    int Board::get_row(char number){
      int row = (number - '0');
      return row;
    }

    void Board::play_game(){
      std::string input;
      //bool is_legal;
      bool white_move = true;       //this tells the program who is to move
      has_moved = false;
      int a = 5;
      while( a != 2){
        while(has_moved == false){
          print_board();
          std::cin >> input;
          if(input == "exit"){
            std::cout << endl << endl;
            a = 2;
            break;
          }
          move_check(input, white_move);
        }
        white_move = !white_move;     //for the next turn, the other player has his turn
        has_moved = false;
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