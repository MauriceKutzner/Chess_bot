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
        white_pawns.push_back(i);   //update pawn positons
      }

      for(int i = 48;  i<56; i++){
        board[i]->set_piece(std::make_unique<Pawn>(false));
        black_pawns.push_back(i);   //update pawn position
      }      
    }

    void Board::print_board(){  
      std::cout << endl << "    A   B   C   D   E   F   G   H " << endl << "  ---------------------------------" << endl << 1;
      for(int i = 0 ; i<64; i++){
        
        if((i%8 == 0) && i != 0){
          std::cout << " |";
          std::cout << " " << (i / 8 ) << endl << "  ---------------------------------" << endl << (i/8+1);
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
          std::cout << " 8" << endl << "  ---------------------------------" << endl<< "    A   B   C   D   E   F   G   H " << endl << endl ;
      
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

      bool is_capture = (input.find('x')!= std::string::npos);
      auto& pawns = get_pawn_list(white_move);

      if(input[input.size() - 2] == '='){    //promotion case
        int index = get_index(input[input.size()-4], input[input.size()-3]);
        cout << endl << "inside promotion loop" << index;
        for(int& i : pawns){
          if(is_valid_promotion(i, index, is_capture, white_move)){
            cout <<endl <<  "valid promotion" << endl;
            if(is_capture){
              board[index]->set_piece(nullptr);
            }

            switch(input[input.size() - 1]){
              case 'Q':
                board[index]->set_piece(std::make_unique<Queen>(white_move));
                board[i]->set_piece(nullptr);
                (white_move ? white_queens : black_queens).push_back(index);
                has_moved = true;
                break;
              case 'R':
                board[index]->set_piece(std::make_unique<Rook>(white_move));
                board[i]->set_piece(nullptr);
                (white_move ? white_rooks : black_rooks).push_back(index);
                has_moved = true;
                break;
              case 'B':
                board[index]->set_piece(std::make_unique<Bishop>(white_move));
                board[i]->set_piece(nullptr);
                (white_move ? white_bishops : black_bishops).push_back(index);
                has_moved = true;

                break;
              case 'N':
                board[index]->set_piece(std::make_unique<Knight>(white_move));
                board[i]->set_piece(nullptr);
                (white_move ? white_knights : black_knights).push_back(index);
                has_moved = true;
                break;
            }
            return;
          }
        }
      }
      int index = get_index(input[input.size()- 2], input[input.size() - 1]);
      if(index_to_row(index) == 8){   //if the pawn is on the last row, it has to promote
        return;
      }

      for(int& i : pawns){
        if(is_valid_pawn_move(i, index, is_capture, white_move)){
          if(is_capture){
            board[index]->set_piece(nullptr);
          }
          board[index]->set_piece(move(board[i]->get_piece()));
          i = index;
          has_moved = true;
          return;
        }
      }
    }
    

    void Board::King_handling(std::string input, bool white_move){
        bool is_capture = (input[1] == 'x');
        int index = get_index(input[1], input[2]);
        int K_pos = (white_move ? King_w_pos : King_b_pos);   //selects correct king

        if(is_valid_king_move(K_pos, index, is_capture, white_move)){
          if(is_capture == true){
            board[index]->set_piece(nullptr);
          }
          board[index]->set_piece(move(board[K_pos]->get_piece()));
          (white_move ? King_w_pos : King_b_pos) = index;
          has_moved = true;
          return;
        }
        else{
          return;
        }
      }

    void Board::Queen_handling(std::string input, bool white_move){
      bool is_capture = (input.find('x') != std::string::npos);   //detect capture

      // Get the last two chars for target square
      int index = get_index(input[input.size() - 2], input[input.size() - 1]);

      // Extract disambiguation info if present (e.g., Qbd4 or Q3d4)
      char disambig_file = '\0';
      char disambig_rank = '\0';
      if (input.size() > (is_capture ? 4 : 3)) {
        // Example: Qbd4 or Qbxd4 → char after 'Q' but before 'x' or target square
        int start_pos = 1; 
        if (is_capture && input[1] == 'x'){
          start_pos = 2;
        }
        if (std::isalpha(input[start_pos])){
          disambig_file = input[start_pos];
        }
        if (std::isdigit(input[start_pos])){
          disambig_rank = input[start_pos];
        }
      }

      // Get correct queen list
      auto& queens = get_queen_list(white_move);

      for(int& i : queens){
        // Skip if disambiguation doesn't match
        int from_file = (i % 8) + 'a';
        int from_rank = (i / 8) + '1';
        if((disambig_file != '\0' && disambig_file != from_file) ||
          (disambig_rank != '\0' && disambig_rank != from_rank)){
          continue;
        }

        if(is_valid_Queen_move(i, index, is_capture, white_move)){
          if (is_capture) {
            board[index]->set_piece(nullptr);
          }
          board[index]->set_piece(move(board[i]->get_piece()));
          i = index; // update queen's stored position
          has_moved = true;
          return;
        }
      }
    // If we get here, no queen made a valid move
    }

    void Board::Rook_handling(std::string input, bool white_move){
      bool is_capture = false;
      int target_file_idx = 1;  // index in input for target file letter
      int target_rank_idx = 2;  // index in input for target rank number

      if(input.length() == 4 && input[1] == 'x'){
        //Rxf3 style
        is_capture = true;
        target_file_idx = 2;
        target_rank_idx = 3;
      }
      else if(input.length() == 4 && input[2] == 'x'){
        //Rfxd3 style (disambiguation + capture)
        is_capture = true;
        target_file_idx = 3;
        target_rank_idx = 4;
      }
      else if(input.length() == 3){
        //Rf3 style (simple move)
        //indices already set
      }
      else if(input.length() == 4 && input[2] != 'x'){
        //Rfd3 style (disambiguation no capture)
        target_file_idx = 2;
        target_rank_idx = 3;
      }

      // Extract target index from input, e.g. 'f3' = file 'f', rank '3'
      int index = get_index(input[target_file_idx], input[target_rank_idx]);
      auto& rooks = get_rook_list(white_move);

      // For disambiguation: file or rank of the from-square may be given
      char disambig_file = '\0';
      char disambig_rank = '\0';

      if(input.length() >= 4 && input[1] != 'x'){
        // If there's a disambiguation char, it will be at input[1]
        if (input[1] >= 'a' && input[1] <= 'h') disambig_file = input[1];
        else if (input[1] >= '1' && input[1] <= '8') disambig_rank = input[1];
      }

      for(int& i : rooks){
        // Check disambiguation matches if present
        int from_file = (i % 8) + 'a';
        int from_rank = (i / 8) + '1';

        if((disambig_file != '\0' && disambig_file != from_file) ||
          (disambig_rank != '\0' && disambig_rank != from_rank)){
          continue;
        }

        if(is_valid_rook_move(i, index, is_capture, white_move)){
          if(is_capture){
            board[index]->set_piece(nullptr);
          }
          board[index]->set_piece(std::move(board[i]->get_piece()));
          i = index;
          has_moved = true;
          return;
        }
      }
    }

    void Board::Bishop_handling(std::string input, bool white_move){
      bool is_capture = (input[1] == 'x');
     
      int index = is_capture
        ? get_index(input[2], input[3]) // capture: skip 'x'
        : get_index(input[1], input[2]); // normal move    

      auto& bishops = get_bishop_list(white_move);

      for(int& i : bishops){
        if(is_valid_bishop_move(i, index, is_capture, white_move)){ 
          if(is_capture){
            board[index]->set_piece(nullptr);
          }
          board[index]->set_piece(move(board[i]->get_piece()));              
          i = index;      //update the position of the bishops
          has_moved = true;
          return;
        }
      
      }
      return;
    } 
    
    void Board::Knight_handling(std::string input, bool white_move){
      bool is_capture = false;
      int target_file_idx = 1;  // index in input for target file letter
      int target_rank_idx = 2;  // index in input for target rank number

      if(input.length() == 4 && input[1] == 'x'){
        // Nxf3 style
        is_capture = true;
        target_file_idx = 2;
        target_rank_idx = 3;
      }
      else if(input.length() == 4 && input[2] == 'x'){
        // Nfxd3 style (disambiguation + capture)
        is_capture = true;
        target_file_idx = 3;
        target_rank_idx = 4;
      }
      else if(input.length() == 3){
        // Nf3 style (simple move)
        // indices already set
      }
      else if(input.length() == 4 && input[2] != 'x'){
        // Nfd3 style (disambiguation no capture)
        target_file_idx = 2;
        target_rank_idx = 3;
      }

      // Extract target index from input, e.g. 'f3' = file 'f', rank '3'
      int index = get_index(input[target_file_idx], input[target_rank_idx]);
      auto& knights = get_knight_list(white_move);

      // For disambiguation: file or rank of the from-square may be given
      char disambig_file = '\0';
      char disambig_rank = '\0';

      if(input.length() >= 4 && input[1] != 'x'){
        // If there's a disambiguation char, it will be at input[1]
        if (input[1] >= 'a' && input[1] <= 'h') disambig_file = input[1];
        else if (input[1] >= '1' && input[1] <= '8') disambig_rank = input[1];
      }

      for(int& i : knights){
        // Check disambiguation matches if present
        int from_file = (i % 8) + 'a';
        int from_rank = (i / 8) + '1';

        if((disambig_file != '\0' && disambig_file != from_file) ||
          (disambig_rank != '\0' && disambig_rank != from_rank)){
          continue;
        }

        if(is_valid_knight_move(i, index, is_capture, white_move)){
          if(is_capture){
            board[index]->set_piece(nullptr);
          }
          board[index]->set_piece(std::move(board[i]->get_piece()));
          i = index;
          has_moved = true;
          return;
        }
      }
    }



    std::vector<int>& Board::get_queen_list(bool white_move){
      return white_move ? white_queens : black_queens;
    }
    
    std::vector<int>& Board::get_rook_list(bool white_move){
      return white_move ? white_rooks : black_rooks;
    }

    std::vector<int>& Board::get_bishop_list(bool white_move){
      return white_move ? white_bishops : black_bishops;
    }

    std::vector<int>& Board::get_knight_list(bool white_move){
      return white_move ? white_knights : black_knights;
    }

    std::vector<int>& Board::get_pawn_list(bool white_move){
      return white_move ? white_pawns : black_pawns;
    }


    bool Board::is_valid_king_move(int from, int to, bool is_capture, bool white_move){

      if(!board[from]->get_piece()){
        return false; // No piece to move
      }

      std::unique_ptr<Piece>& piece = board[from]->get_piece();

      // Must be a rook of the correct side
      if(piece->type != 0 || piece->color != white_move){
        return false;
      }

    // Must be a legal rook move
      if(!check_k_index(to, from)){
        return false;
      }

      if(is_capture){
        // Capture must be against the opposite color
        return board[to]->get_piece() &&
               board[to]->get_piece()->color != white_move;
      } 
      else{
        // Non-capture must land on an empty square
        return board[to]->get_piece() == nullptr;
      }
    }

    bool Board::is_valid_Queen_move(int from, int to, bool is_capture, bool white_move){
      
      if(!board[from]->get_piece()){
        return false; // No piece to move
      }

      std::unique_ptr<Piece>& piece = board[from]->get_piece();

      // Must be a queen of the correct side
      if(piece->type != 1 || piece->color != white_move){
        return false;
      }

    // Must be a legal rook move
      if(!check_q_index(to, from)){
        return false;
      }

      if(is_capture){
        // Capture must be against the opposite color
        return board[to]->get_piece() &&
               board[to]->get_piece()->color != white_move;
      } 
      else{
        // Non-capture must land on an empty square
        return board[to]->get_piece() == nullptr;
      }
    }

    bool Board::is_valid_rook_move(int from, int to, bool is_capture, bool white_move){

      if(!board[from]->get_piece()){
        return false; // No piece to move
      }

      std::unique_ptr<Piece>& piece = board[from]->get_piece();

      // Must be a rook of the correct side
      if(piece->type != 2 || piece->color != white_move){
        return false;
      }

    // Must be a legal rook move
      if(!check_r_index(to, from)){
        return false;
      }

      if(is_capture){
        // Capture must be against the opposite color
        return board[to]->get_piece() &&
               board[to]->get_piece()->color != white_move;
      } 
      else{
        // Non-capture must land on an empty square
        return board[to]->get_piece() == nullptr;
      }
    }

    bool Board::is_valid_bishop_move(int from, int to, bool is_capture, bool white_move){

      if(!board[from]->get_piece()){
        return false; // No piece to move
      }

      std::unique_ptr<Piece>& piece = board[from]->get_piece();

      // Must be a rook of the correct side
      if(piece->type != 3 || piece->color != white_move){
        return false;
      }

    // Must be a legal rook move
      if(!check_b_index(to, from)){
        return false;
      }

      if(is_capture){
        // Capture must be against the opposite color
        return board[to]->get_piece() &&
               board[to]->get_piece()->color != white_move;
      } 
      else{
        // Non-capture must land on an empty square
        return board[to]->get_piece() == nullptr;
      }
    }

    bool Board::is_valid_knight_move(int from, int to, bool is_capture, bool white_move){

      if(!board[from]->get_piece()){
        return false; // No piece to move
      }

      std::unique_ptr<Piece>& piece = board[from]->get_piece();

      // Must be a rook of the correct side
      if(piece->type != 4 || piece->color != white_move){
        return false;
      }

    // Must be a legal rook move
      if(!check_n_index(to, from)){
        return false;
      }

      if(is_capture){
        // Capture must be against the opposite color
        return board[to]->get_piece() &&
               board[to]->get_piece()->color != white_move;
      } 
      else{
        // Non-capture must land on an empty square
        return board[to]->get_piece() == nullptr;
      }
    }

    bool Board::is_valid_pawn_move(int from, int to, bool is_capture, bool white_move){
      if(!board[from]->get_piece()){
        return false; // No piece to move
      }
      std::unique_ptr<Piece>& piece = board[from]->get_piece();
      if(piece->type != 5 || piece->color != white_move){
        return false;
      }
      if(!check_p_index(to, from, is_capture, white_move)){
        return false;
      }

      if(is_capture){
        // Capture must be against the opposite color
        return board[to]->get_piece() &&
               board[to]->get_piece()->color != white_move;
      } 
      else{
        // Non-capture must land on an empty square
        return board[to]->get_piece() == nullptr;
      }
    }

    bool Board::is_valid_promotion(int from, int to, bool is_capture, bool white_move){
      if(index_to_row(from) != 7){
        return false; //pawn is not on the last row
      }
      if(!board[from]->get_piece()){
        return false; // No piece to move
      }
      std::unique_ptr<Piece>& piece = board[from]->get_piece();
      if(piece->type != 5 || piece->color != white_move){
        return false;
      }
      if(!check_p_index(to, from, is_capture, white_move)){
        return false;
      }

      if(is_capture){
        // Capture must be against the opposite color
        return board[to]->get_piece() &&
               board[to]->get_piece()->color != white_move;
      } 
      else{
        // Non-capture must land on an empty square
        return board[to]->get_piece() == nullptr;
      }

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

    bool Board::check_r_index(int targ_index, int R_pos){
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
    
    bool Board::check_n_index(int targ_index, int N_pos){
      static const int jumps[8] = {-17, -15, -10, -6, 6, 10, 15, 17};

      int start_row = N_pos / 8;
      int start_col = N_pos % 8;

      for(int j : jumps){
        int next_pos = N_pos + j;

        if(next_pos < 0 || next_pos >= 64){
          continue;
        }

        int next_row = next_pos / 8;
        int next_col = next_pos % 8;

        if((std::abs(next_row - start_row) == 2 && std::abs(next_col - start_col) == 1) ||
          (std::abs(next_row - start_row) == 1 && std::abs(next_col - start_col) == 2)){
          if(next_pos == targ_index){
            return true;
          }
        }
      }

      return false;
    }

    bool Board::check_p_index(int to, int from, bool is_capture, bool white_move) {
      int from_file = from % 8;
      int from_rank = from / 8;
      int to_file   = to % 8;
      int to_rank   = to / 8;

      int rank_diff = to_rank - from_rank;
      int file_diff = to_file - from_file;

      if(white_move){
        if(is_capture){
          // White captures diagonally one square
          return (rank_diff == 1 && std::abs(file_diff) == 1);
        } 
        else{
          // One step forward or two steps from starting rank (rank 1 in 0-index)
          if (rank_diff == 1 && file_diff == 0){
            return true;
          }
          if (from_rank == 1 && rank_diff == 2 && file_diff == 0) {
            // Check square in between is empty
            return (board[from + 8]->get_piece() == nullptr);
          }
          return false;
        }
    } 
      else { // Black move
        if(is_capture){
          // Black captures diagonally one square
          return (rank_diff == -1 && std::abs(file_diff) == 1);
        }
        else{
          // One step forward or two steps from starting rank (rank 6 in 0-index)
          if (rank_diff == -1 && file_diff == 0){
            return true;
          }
          if (from_rank == 6 && rank_diff == -2 && file_diff == 0){
            // Check square in between is empty
            return (board[from - 8]->get_piece() == nullptr);
          }
          return false;
        }
    }
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

    int Board::index_to_row(int index){
      return (1 + (index / 8));
    }

    int Board::index_to_col(int index){
      return (1 + (index % 8));
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

int main(){
  Board B;

  B.play_game();

  return 0;
}