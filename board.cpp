#include <iostream>
#include <array>
#include "board.h"
#include "square.h"
#include <memory>
#include "pieces.h"
#include <string>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

    /*Overarching functions*/

    void clear_console() {
        system("cls");
    }    

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

    void Board::print_board() {
    std::cout << "\n    A   B   C   D   E   F   G   H \n";
    std::cout << "  ---------------------------------\n";

    for (int row = 0; row < 8; row++) {
        std::cout << (row + 1); // print row number on the left

        for (int col = 0; col < 8; col++) {
            int idx = row * 8 + col;
            std::unique_ptr<Piece>& piece = board[idx]->get_piece();

            if (piece) {
                char letter = return_piece_letter(return_p_type(piece));
                if (piece->color == false) { // black
                    letter = char(tolower(letter));
                }
                std::cout << " | " << letter;
            } else {
                std::cout << " |  ";
            }
        }

        std::cout << " | " << (row + 1) << "\n"; // row number at the right
        std::cout << "  ---------------------------------\n";
    }

    std::cout << "    A   B   C   D   E   F   G   H \n\n";
}
/*
    void Board::move_check(std::string input, bool white_move){
      UndoState undo;
      Move move;
      if(input[0]== 'o' || input[0] == '0' || input[0] == 'O'){     //special case for castles
        bool length = (input.length() < 4);
        move = Castles_handling(length, white_move);
        
          if(move.is_valid){

            undo = make_move(move,white_move);
            if(check_for_checks(white_move)){
              std::cout << "King in Check!" << endl;
              unmake_move(move, undo, white_move);
            }
          }
        return;
      }
      
      else if(isupper(input[0]) == false){      //if the first letter is not capitalized, it is a pawn move
        move = pawn_handling(input, white_move);
        if(move.is_valid){
          undo = make_move(move,white_move);
          if(check_for_checks(white_move)){
            std::cout << "King in Check!" << endl;
            unmake_move(move, undo, white_move);    
          }
        }
        else{
          std::cout<< "not valid" << endl;
        }
        return;
      }

      else switch(input[0]){
        case 'K':
          move = King_handling(input, white_move);
          if(move.is_valid){
            undo = make_move(move,white_move);
            if(check_for_checks(white_move)){
              std::cout << "King in Check!" << endl;

              unmake_move(move, undo, white_move);
            }
          }
          
          return;
        case 'Q':
        move = Queen_handling(input, white_move);
          if(move.is_valid){
            undo = make_move(move,white_move);
            if(check_for_checks(white_move)){
              std::cout << "King in Check!" << endl;
              unmake_move(move, undo, white_move);
            }
          }
          return;
        case 'R':
          move = Rook_handling(input, white_move);
          if(move.is_valid){
            undo = make_move(move,white_move);
            if(check_for_checks(white_move)){
              std::cout << "King in Check!" << endl;
              unmake_move(move, undo, white_move);
            }
          }
          return;
        case 'B':
          move = Bishop_handling(input, white_move);
          if(move.is_valid){
            undo = make_move(move,white_move);
            if(check_for_checks(white_move)){
              std::cout << "King in Check!" << endl;
              unmake_move(move, undo, white_move);
            }
          }
          return;
        case 'N':
          move = Knight_handling(input, white_move);
          if(move.is_valid){
            undo = make_move(move,white_move);
            if(check_for_checks(white_move)){
              std::cout << "King in Check!" << endl;
              unmake_move(move, undo, white_move);
            }
          }
          return;
      }
    }
*/
    void Board::remove_piece_index(int type, int index, bool white_move){
      switch(type){
        case 1:{     //Queen got captured
          std::vector<int>& queens = (!white_move ? white_queens : black_queens);
          queens.erase(std::remove(queens.begin(), queens.end(), index), queens.end());
          return;
        }
        case 2:{     //Rook got captured
          std::vector<int>& rooks = (!white_move ? white_rooks : black_rooks);
          rooks.erase(std::remove(rooks.begin(), rooks.end(), index), rooks.end());
          return;
        }
        case 3:{     //Bishop got captured
          std::vector<int>& bishops = (!white_move ? white_bishops : black_bishops);
          bishops.erase(std::remove(bishops.begin(), bishops.end(), index), bishops.end());
          return;
        }
        case 4:{     //Knight got captured
          std::vector<int>& knights = (!white_move ? white_knights : black_knights);
          knights.erase(std::remove(knights.begin(), knights.end(), index), knights.end());
          return;
        }
        case 5:{     //pawn got captured
          std::vector<int>& pawns = (!white_move ? white_pawns : black_pawns);
          pawns.erase(std::remove(pawns.begin(), pawns.end(), index), pawns.end());
          return;
        }
        default:{
          return;
        }
      }
    }

    void Board::add_piece_index(int type, int index, bool white_move){
      switch(type){
        case 1:{     //Queen got added
          std::vector<int>& queens = (!white_move ? white_queens : black_queens);
          queens.push_back(index);
          return;
        }
        case 2:{     //Rook got captured
          std::vector<int>& rooks = (!white_move ? white_rooks : black_rooks);
          rooks.push_back(index);
          return;
        }
        case 3:{     //Bishop got captured
          std::vector<int>& bishops = (!white_move ? white_bishops : black_bishops);
          bishops.push_back(index);
          return;
        }
        case 4:{     //Knight got captured
          std::vector<int>& knights = (!white_move ? white_knights : black_knights);
          knights.push_back(index);
          return;
        }
        case 5:{     //pawn got captured
          std::vector<int>& pawns = (!white_move ? white_pawns : black_pawns);
          pawns.push_back(index);
          return;
        }
        default:{
          return;
        }
      }
    }

    void Board::play_game(){
      std::string input;
      //bool is_legal;
      bool white_move = true;       //this tells the program who is to move
      has_moved = false;
      int a = 5;
      bool correct;
      while( a != 2){
        do{
          print_board();
          std::cout << (white_move ? "whites turn" : "blacks turn") << endl;
          std::cin >> input;
          if(input.length() < 2 ){
            continue;
          }
          if(input == "exit"){
            std::cout << endl << endl;
            a = 2;
            break;
          }
          correct = input_to_var(input, white_move);
        }while(!correct);
        white_move = !white_move;     //for the next turn, the other player has his turn
        correct = false;
        has_moved = false;
        //clear_console();
        
      }
    }
    
    Board::UndoState Board::make_move(const Move& move, bool white_move){

      UndoState undo;

      // Save previous state
      undo.prev_king_w_pos = King_w_pos;
      undo.prev_king_b_pos = King_b_pos;

      undo.prev_white_queens = white_queens;
      undo.prev_black_queens = black_queens;

      undo.prev_white_rooks = white_rooks;
      undo.prev_black_rooks = black_rooks;

      undo.prev_white_bishops = white_bishops;
      undo.prev_black_bishops = black_bishops;

      undo.prev_white_knights = white_knights;
      undo.prev_black_knights = black_knights;

      undo.prev_white_pawns = white_pawns;
      undo.prev_black_pawns = black_pawns;


      //auto& piece = board[move.from]->get_piece();
      int piece_type = board[move.from]->get_piece()->type;
      undo.prev_has_moved = board[move.from]->get_piece()->has_moved;
      

      // Handle captures
      if(move.is_capture){
        if(move.is_en_passant){
          int captured_index = white_move ? move.to - 8 : move.to + 8;
          undo.captured_piece = std::move(board[captured_index]->get_piece());    //save the captured piece for possible undoing
          remove_piece_index(undo.captured_piece->type, captured_index, !white_move);   //remove the index of the captrued piece
          board[captured_index]->set_piece(nullptr);
        } 
        else{
          undo.captured_piece = std::move(board[move.to]->get_piece());
          remove_piece_index(undo.captured_piece->type, move.to, !white_move);
          board[move.to]->set_piece(nullptr);     //make the target square empty
        }
      } 
      else{     
        undo.captured_piece = nullptr;
      }

      // Move piece
      board[move.to]->set_piece(std::move(board[move.from]->get_piece()));
      //board[move.from]->set_piece(nullptr);
      board[move.to]->get_piece()->has_moved = true;
      // Update piece lists
      //print_board();
      switch(piece_type){
        case (0):{
          int King_pos = white_move ? King_w_pos : King_b_pos;
          King_pos = move.to;
          break;
        }
        case (1):{
          auto& Queen_vec = white_move ? white_queens : black_queens;
          for (int& idx : Queen_vec){
            if (idx == move.from){
              idx = move.to;
            }
          }
          break;
        }
        case (2):{
          auto& Rook_vec = white_move ? white_rooks : black_rooks;
          for (int& idx : Rook_vec){
            if (idx == move.from){
              idx = move.to;
            }
          }
          break;
        }
        case (3):{
          auto& Bishop_vec = white_move ? white_bishops: black_bishops;
          for (int& idx : Bishop_vec){
            if (idx == move.from){
              idx = move.to;
            }
          }
          break;
        }
        case (4):{
          auto& Knight_vec = white_move ? white_knights : black_knights;
          for (int& idx : Knight_vec){
            if (idx == move.from){
              idx = move.to;
            }
          }
          break;
        }
        case (5):{
          auto& pawns_vec = white_move ? white_pawns : black_pawns;
          for (int& idx : pawns_vec){
            if (idx == move.from){
              idx = move.to;
            }
          }
          
          break;
        }
      }
      
      if (move.is_castle){
        // Handle rook movement
        if (move.to > move.from) {  // kingside
          undo.rook_from = white_move ? 7 : 63;
          undo.rook_to = white_move ? 5 : 61;
        } else {                    // queenside
          undo.rook_from = white_move ? 0 : 56;
          undo.rook_to = white_move ? 3 : 59;
        }
        // Save rook's has_moved flag before overwriting
        if (board[undo.rook_from] && board[undo.rook_from]->get_piece()) {
          undo.rook_prev_has_moved = board[undo.rook_from]->get_piece()->has_moved;
        } 
        else {
          undo.rook_prev_has_moved = false; // fallback
        }
        

        board[undo.rook_to]->set_piece(std::move(board[undo.rook_from]->get_piece()));    //move selected rook
        board[undo.rook_from]->set_piece(nullptr);

        if (board[undo.rook_to] && board[undo.rook_to]->get_piece()){
          board[undo.rook_to]->get_piece()->has_moved = true;
        }

        // Update rook positions
        auto& rooks_vec = white_move ? white_rooks : black_rooks;
        for (int& idx : rooks_vec){ 
          if(idx == undo.rook_from){
            idx = undo.rook_to;
          }
        }
      }
      

      // Handle promotion
      if (move.promotion_type != -1){
        board[move.to]->set_piece(nullptr);
        remove_piece_index(piece_type, move.from, white_move);
        
        switch(move.promotion_type){

          case 1: board[move.to]->set_piece(std::make_unique<Queen>(white_move));
                  (white_move ? white_queens : black_queens).push_back(move.to);
                  break;
          case 2: board[move.to]->set_piece(std::make_unique<Rook>(white_move));
                  (white_move ? white_rooks : black_rooks).push_back(move.to);
                  break;
          case 3: board[move.to]->set_piece(std::make_unique<Bishop>(white_move));
                  (white_move ? white_bishops : black_bishops).push_back(move.to);
                  break;
          case 4: board[move.to]->set_piece(std::make_unique<Knight>(white_move));
                  (white_move ? white_knights : black_knights).push_back(move.to);
                  break;
        }
       
      }

      // Update just_moved_two for pawns
      if(board[move.to]->get_piece()->type == 5 ){
        Pawn* p = dynamic_cast<Pawn*>(board[move.to]->get_piece().get());
        if (p){
          undo.prev_just_moved_two = p->just_moved_two;
          p->just_moved_two = (std::abs(move.to - move.from) == 16);
        }
      }
      has_moved = true;
      return undo;
    }

    void Board::unmake_move(Move& move, UndoState& undo, bool white_move){
      auto& moved_piece = board[move.to]->get_piece();
      board[move.from]->set_piece(std::move(moved_piece));  //move the piece back

      board[move.from]->get_piece()->has_moved = undo.prev_has_moved;     //undo move marker

      //undo flag for pawns moving 2 squares
      if(board[move.from]->get_piece()->type == 5){
        Pawn* p = dynamic_cast<Pawn*>(moved_piece.get());
        if (p){
          p->just_moved_two = undo.prev_just_moved_two;
        }
      }

      //undo deletion of piece index
      add_piece_index(board[move.from]->get_piece()->type, move.from, white_move);
      //handle captures and en passent
      if(move.is_capture){
        if(move.is_en_passant){
          int captured_index = white_move ? move.to - 8 : move.to + 8;
          board[captured_index]->set_piece(std::move(undo.captured_piece));
          add_piece_index(board[captured_index]->get_piece()->type, captured_index, !white_move);
        }
        else{
          add_piece_index(undo.captured_piece->type, move.to, !white_move); //readd index
          board[move.to]->set_piece(std::move(undo.captured_piece));    //return captured piece to original square
        }
      }
       
      //handle castling
      if(move.is_castle){
        board[undo.rook_from]->set_piece(std::move(board[undo.rook_to]->get_piece()));
        board[undo.rook_to]->set_piece(nullptr);
        if(board[undo.rook_from] && board[undo.rook_from]->get_piece()){
          board[undo.rook_from]->get_piece()->has_moved = undo.rook_prev_has_moved;
        }
      }

      //promotion case
      if(move.promotion_type != -1){
        remove_piece_index(board[move.to]->get_piece()->type, move.to, white_move);
        board[move.to]->set_piece(nullptr);
        board[move.from]->set_piece(std::make_unique<Pawn>(white_move));
        auto& pawns_vec = white_move ? white_pawns : black_pawns;
        pawns_vec.push_back(move.from);
      }

      //restore piece indices
      King_w_pos       = undo.prev_king_w_pos;
      King_b_pos       = undo.prev_king_b_pos;
      white_queens     = undo.prev_white_queens;
      black_queens     = undo.prev_black_queens;
      white_rooks      = undo.prev_white_rooks;
      black_rooks      = undo.prev_black_rooks;
      white_bishops    = undo.prev_white_bishops;
      black_bishops    = undo.prev_black_bishops;
      white_knights    = undo.prev_white_knights;
      black_knights    = undo.prev_black_knights;
      white_pawns      = undo.prev_white_pawns;
      black_pawns      = undo.prev_black_pawns;
    }

    bool Board::check_for_checks(bool white_move){
      int king_pos = white_move ? King_w_pos : King_b_pos;

      int king_row = index_to_row(king_pos);
      int king_col = index_to_col(king_pos);

      // pawn moves
      int pawn_dir = (white_move ? 1: -1);
      for(int dc : {-1, 1}){
        int r = king_row + pawn_dir;
        int c = king_col + dc;
        if(is_on_board(r, c)){

          int idx = rc_to_index(r, c);
          if(board[idx] && board[idx]->get_piece()){
            auto& p = board[idx]->get_piece();
            if (p->type == 5 && p->color != white_move){ 
              return true;
            }
          }
        }
      }
        // === 2. Knight attacks ===
      const int knight_moves[8][2] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
      };
      int i =1;

      for (auto [dr, dc] : knight_moves){
        int r = king_row + dr;
        int c = king_col + dc;
        if (is_on_board(r, c)) {
          int idx = rc_to_index(r, c);
          if (board[idx] && board[idx]->get_piece()) {
            auto& p = board[idx]->get_piece();
            if (p->type == 4 && p->color != white_move) return true;
          }
        }
        i++;
      }
      
      // === 3. Sliding pieces (rook/queen: straight lines, bishop/queen: diagonals) ===
      const int rook_dirs[4][2]   = {{1,0}, {-1,0}, {0,1}, {0,-1}};
      const int bishop_dirs[4][2] = {{1,1}, {1,-1}, {-1,1}, {-1,-1}};

      // Rook/Queen
      for (auto [dr, dc] : rook_dirs){
        int r = king_row, c = king_col;
        while (true){
          r += dr; c += dc;
          if (!is_on_board(r, c)){ 
            break;
          }
          int idx = rc_to_index(r, c);
          if (board[idx] && board[idx]->get_piece()){
            auto& p = board[idx]->get_piece();
            if (p->color != white_move && (p->type == 2 || p->type == 1)){
              return true; // rook or queen
            }
            break;
          }
        }
      }
      // Bishop/Queen
      for (auto [dr, dc] : bishop_dirs) {
        int r = king_row, c = king_col;
        while(true){
          r += dr; c += dc;
          if (!is_on_board(r, c)){ 
            break;
          }
          int idx = rc_to_index(r, c);
          if(board[idx] && board[idx]->get_piece()){
            auto& p = board[idx]->get_piece();
            if (p->color != white_move && (p->type == 3 || p->type == 1)){
              
              return true;
            } // bishop or queen
            break;
          }
        }
      }

      // === 4. Enemy king (edge case: adjacent square) ===
      for (int dr=-1; dr<=1; dr++) {
        for (int dc=-1; dc<=1; dc++) {
          if (dr == 0 && dc == 0) continue;
          int r = king_row + dr;
          int c = king_col + dc;
          if (is_on_board(r, c)) {
            int idx = rc_to_index(r, c);
            if (board[idx] && board[idx]->get_piece()) {
              auto& p = board[idx]->get_piece();
              if (p->type == 0 && p->color != white_move) return true;
            }
          }
        }
      }

    
      return false;
    }

    bool Board::is_on_board(int row, int col){
      return (row >= 0 && row < 8 && col >= 0 && col < 8);
    }

    int Board::rc_to_index(int row, int col){
      return (((row)*8)+(col));
    }
/*

    vector<Board::Move> Board::find_moves(bool white_move){
      /*vector<Move> legal_moves;
      auto pawns = (white_move ? white_pawns : black_pawns);
      for(auto& i : pawns){
        
      }
     return 
    }
*/
    bool Board::input_to_var(std::string input, bool white_move){
      Move move;
      UndoState undo;
      if(input[0]== 'o' || input[0] == '0' || input[0] == 'O'){     //special case for castles
        bool length = (input.length() < 4);


        move = Castles_handling(length, white_move);
        
          if(move.is_valid){

            undo = make_move(move,white_move);
            if(check_for_checks(white_move)){
              std::cout << "King in Check!" << endl;
              unmake_move(move, undo, white_move);
              return false;
            }
            return true;
          }
        return false;
      }
      else if(isupper(input[0]) == false){      //if the first letter is not capitalized, it is a pawn move
        move = pawn_handling(input,move, white_move, false);
        if(move.is_valid){
          undo = make_move(move,white_move);
          if(check_for_checks(white_move)){
            std::cout << "King in Check!" << endl;
            unmake_move(move, undo, white_move);
            return false;    
          }
          return true;
        }
        else{
          std::cout<< "not valid" << endl;
          return false;
        }
        return true;
      }

      else switch(input[0]){
        case 'K':
          for(auto i: input){
            if(i == 'x'){
              move.is_capture =true;
              break;
            }
          }
          move.from = (white_move ? King_w_pos : King_b_pos);
          move.to = get_index(input[input.length()-2],input[input.length()-1]);
          move = King_handling(move, white_move);
          if(move.is_valid){
            undo = make_move(move,white_move);
            if(check_for_checks(white_move)){
              std::cout << "King in Check!" << endl;

              unmake_move(move, undo, white_move);
              return false;
            }
            return true;
          }
          
          return false;
        case 'D':
        case 'Q':        
          move = Queen_handling(input, move, white_move, false);
          if(move.is_valid){
            undo = make_move(move,white_move);
            if(check_for_checks(white_move)){
              std::cout << "King in Check!" << endl;

              unmake_move(move, undo, white_move);
              return false;
            }
            return true;
          }
          
          return false;

        case 'R': 
        case 'T':    
          
          move = Rook_handling(input, move, white_move, false);
          if(move.is_valid){
            
            undo = make_move(move,white_move);
            print_board();
            if(check_for_checks(white_move)){
              std::cout << "King in Check!" << endl;

              unmake_move(move, undo, white_move);
              return false;
            }
            return true;
          }
          
          return false;
        case 'B':
        case 'L':
          move = Bishop_handling(input, move, white_move, false);
          if(move.is_valid){
              undo = make_move(move,white_move);
            if(check_for_checks(white_move)){
              std::cout << "King in Check!" << endl;
              unmake_move(move, undo, white_move);
              return false;
            }
            return true;
          }
          return false;
        case 'N':
        case 'S':
          move = Knight_handling(input, move, white_move, false);
          if(move.is_valid){
              undo = make_move(move,white_move);
            if(check_for_checks(white_move)){
              std::cout << "King in Check!" << endl;
              unmake_move(move, undo, white_move);
              return false;
            }
            return true;
          }
          return false;
        default:
          return false;

    }
  }

    /*Handling functions*/
    
    Board::Move Board::King_handling(Board::Move move, bool white_move){
        
        if(is_valid_king_move(move.from, move.to, move.is_capture, white_move)){
          move.is_valid = true;
          return move;
        }
        move.is_valid = false;
        return move;
    }
      
    Board::Move Board::Queen_handling(std::string input, Board::Move move, bool white_move, bool algorithm){
      if(algorithm == true && is_valid_Queen_move(move.from, move.to, move.is_capture, white_move)){
        //easier to use for move generation
        move.is_valid = true;
        return move;
      }

      else if(algorithm == false){
        //more suitable for normal input
        move.is_capture = (input.find('x') != std::string::npos);   //detect capture

        // Get the last two chars for target square
        move.to = get_index(input[input.size() - 2], input[input.size() - 1]);

        // Extract disambiguation info if present (e.g., Qbd4 or Q3d4)
        char disambig_file = '\0';
        char disambig_rank = '\0';
        if (input.size() > (move.is_capture ? 4 : 3)) {
          // Example: Qbd4 or Qbxd4 → char after 'Q' but before 'x' or target square
          int start_pos = 1; 
          if (move.is_capture && input[1] == 'x'){
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

          if(is_valid_Queen_move(i, move.to, move.is_capture, white_move)){
            move.from = i;
            move.is_valid = true;
            return move;
          }
        }
      }
      move.is_valid = false;
      return move;
    }

    Board::Move Board::Rook_handling(std::string input, Board::Move move, bool white_move, bool algorithm){
      if(algorithm == true && is_valid_rook_move(move.from, move.to, move.is_capture, white_move)){
        //easier to use for move generation
        move.is_valid = true;
        return move;
      }
      if(algorithm == false){
        std::cout<<"in correct if statement" << endl;
        move.is_capture = false;
        int target_file_idx = 1;  // index in input for target file letter
        int target_rank_idx = 2;  // index in input for target rank number

        if(input.length() == 4 && input[1] == 'x'){
          //Rxf3 style
          move.is_capture = true;
          target_file_idx = 2;
          target_rank_idx = 3;
        }
        else if(input.length() == 4 && input[2] == 'x'){
          //Rfxd3 style (disambiguation + capture)
          move.is_capture = true;
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
        move.to = get_index(input[target_file_idx], input[target_rank_idx]);
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

          if(is_valid_rook_move(i, move.to, move.is_capture, white_move)){
            move.from = i;
            move.is_valid = true;
            return move;
          }
        }
      }
      move.is_valid = true;
      return move;
    }

    Board::Move Board::Bishop_handling(std::string input, Board::Move move, bool white_move, bool algorithm){
      if(algorithm == true && is_valid_bishop_move(move.from, move.to, move.is_capture, white_move)){
        //easier to use for move generation
        move.is_valid = true;
        return move;
      }
      else if(algorithm == false){
        move.is_capture = (input[1] == 'x');
      
        move.to = move.is_capture
          ? get_index(input[2], input[3]) // capture: skip 'x'
          : get_index(input[1], input[2]); // normal move    

        auto& bishops = get_bishop_list(white_move);

        for(int& i : bishops){
          if(is_valid_bishop_move(i, move.to, move.is_capture, white_move)){
            move.from = i;
            move.is_valid = true;
            return move;
          }
        }
      }
      move.is_valid = false;
      return move;
    } 
    
    Board::Move Board::Knight_handling(std::string input, Board::Move move, bool white_move, bool algorithm){
      if(algorithm == true && is_valid_knight_move(move.from, move.to, move.is_capture, white_move)){
        //easier to use for move generation
        move.is_valid = true;
        return move;
      }
      else if(algorithm == false){
        move.is_capture = false;
        int target_file_idx = 1;  // index in input for target file letter
        int target_rank_idx = 2;  // index in input for target rank number

        if(input.length() == 4 && input[1] == 'x'){
          // Nxf3 style
          move.is_capture = true;
          target_file_idx = 2;
          target_rank_idx = 3;
        }
        else if(input.length() == 4 && input[2] == 'x'){
          // Nfxd3 style (disambiguation + capture)
          move.is_capture = true;
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
        //int index = get_index(input[target_file_idx], input[target_rank_idx]);
        move.to = get_index(input[target_file_idx], input[target_rank_idx]);
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

          if(is_valid_knight_move(i, move.to, move.is_capture, white_move)){
            move.from = i;
            move.is_valid = true;
            return move;
          }
          
        }
      }
      move.is_valid = false;
      return move;
    }

    Board::Move Board::pawn_handling(std::string input, Board::Move move, bool white_move, bool algorithm){  //include en passent
      if(algorithm == true && is_valid_pawn_move(move.from, move.to, move.is_capture, white_move)){
        //easier to use for move generation
        move.is_valid = true;
        return move;
      }
      if(algorithm == false){
        move.is_capture = (input.find('x')!= std::string::npos);
        auto& pawns = get_pawn_list(white_move);
        

        if(input[input.size() - 2] == '='){    //promotion case
          move.to = get_index(input[input.size()-4], input[input.size()-3]);
          std::cout << "detected promotion" << endl;
          for(int& i : pawns){

            if(is_valid_promotion(i, move.to, move.is_capture, white_move)){
              std::cout << "is valid promotion" << endl;
              move.from = i;
              switch(input[input.size() - 1]){
                case 'Q':
                  move.promotion_type = 1;
                  break;
                case 'R':
                  move.promotion_type = 2;
                  break;
                case 'B':
                  move.promotion_type = 3;
                  break;
                case 'N':
                  move.promotion_type = 4;
                  break;
              }
              move.is_valid = true;
              return move;
            }
          }
        }

        else{

          move.to = get_index(input[input.size()- 2], input[input.size() - 1]);
          if(index_to_row(move.to) == 8){   //if the pawn is on the last row, it has to promote
            move.is_valid = false;
            return move;
          }
          
          for(int& i : pawns){
            if(is_valid_en_passant(i, move.to, move.is_capture, white_move)){
              move.from = i;
              move.is_en_passant = true;
              move.is_valid = true;
              return move;
            }

            if(is_valid_pawn_move(i, move.to, move.is_capture, white_move)){
              move.from = i;
              move.is_valid = true;
              return move;
            }
          }
        }
      }
      move.is_valid = false;
      return move;
    }

    Board::Move Board::Castles_handling(bool length, bool white_move){
      Move move;
      if(is_valid_castling(length, white_move)){
        move.is_castle = true;
        move.from = (white_move ? 4 : 60);
        move.to = (length ? (white_move ? 6 : 62) : (white_move ? 2 : 58));
        move.is_valid = true;
        return move;
      }
      move.is_valid = false;
      return move;
    }

    /*Get List functions*/

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

/*is valid functions*/

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
      if(index_to_row(from) != 6){
        std::cout << "wrong row" << endl;
        return false; //pawn is not on the last row
      }
      if(!board[from]->get_piece()){
        std::cout << " did not get piece " << endl;
        return false; // No piece to move
      }
      std::unique_ptr<Piece>& piece = board[from]->get_piece();
      if(piece->type != 5 || piece->color != white_move){
        std::cout << " something color" << endl;
        return false;
      }
      if(!check_p_index(to, from, is_capture, white_move)){
        std::cout << "check p index function " << endl;
        return false;
      }

      if(is_capture){
        // Capture must be against the opposite color
        return board[to]->get_piece() &&
               board[to]->get_piece()->color != white_move;
      } 
      else{
        // Non-capture must land on an empty square
        std::cout << "something wiht getting the empty square" << endl;
        return board[to]->get_piece() == nullptr;
      }

    }
    
    bool Board::is_valid_en_passant(int from, int to, bool is_capture, bool white_move){
      /*
      if(index_to_row(from) == 4 || index_to_row(from) == 3){

        return false; //pawn is on the incorrect row to perform en passent
      }*/
      if(!board[from]->get_piece()){
        return false;   //no piece to move
      }

      std::unique_ptr<Piece>& piece = board[from]->get_piece();
      if(piece->type != 5 || piece->color != white_move){
        return false; //either incorrect color or type
      }
      if(!check_en_passant(to, from, white_move)){
        return false;   //does not meet the en passent requirements
      }
      
      
      if(is_capture){
        return true;
      }
      else{
        return false; //en passent is always a capture
      }

    }

    bool Board::is_valid_castling(bool length, bool white_move){
      if (length == false){
        int r_index = (white_move ? 0 : 56);
        int k_index = (white_move ? 4 : 60);
        
        if(!board[r_index]->get_piece() ||    
          !board[k_index]->get_piece() ||
          board[r_index + 1]->get_piece() != nullptr ||
          board[r_index + 2]->get_piece() != nullptr ||
          board[r_index + 3]->get_piece() != nullptr){

          return false;
        }
        if(!(board[r_index]->get_piece()->type == 2) || !(board[k_index]->get_piece()->type == 0)){   //chekc if the pieces are rook and king

          return false;
        }

        Rook* rook = dynamic_cast<Rook*>(board[r_index]->get_piece().get());
        King* king = dynamic_cast<King*>(board[k_index]->get_piece().get());

        if(rook->has_n_moved == false || king->has_n_moved == false){   //cehck if either rook or king have moved
          return false;
        }
        
        return true;
      }
      else if (length == true){

        int r_index = (white_move ? 7 : 63);
        int k_index = (white_move ? 4 : 60);

        if(!board[r_index]->get_piece() ||    
          !board[k_index]->get_piece() ||
          board[r_index - 1]->get_piece() != nullptr ||
          board[r_index - 2]->get_piece() != nullptr){
          return false;
        }
        if(!(board[r_index]->get_piece()->type == 2) || !(board[k_index]->get_piece()->type == 0)){   //chekc if the pieces are rook and king
          return false;
        }

        Rook* rook = dynamic_cast<Rook*>(board[r_index]->get_piece().get());
        King* king = dynamic_cast<King*>(board[k_index]->get_piece().get());

        if(rook->has_n_moved == false || king->has_n_moved == false){   //cehck if either rook or king have moved
          return false;
        }
        
        return true;
      }
      return false;
    }

    /*Check index functions*/

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
/*
    bool Board::check_en_passant(int to, int from, bool white_move){
      // Pawns can only move diagonally by 1 file (col) and 1 rank (row) for en passant
      int from_row = index_to_row(from);
      int from_col = index_to_col(from);
      int to_row   = index_to_row(to);
      int to_col   = index_to_col(to);

      // Basic diagonal move check
      if (std::abs(from_col - to_col) != 1) return false;
      if ((white_move && to_row - from_row != 1) || (!white_move && from_row - to_row != 1)) {
        return false;
      }

      // Destination square must be empty
      if (board[to]->get_piece() != nullptr){
        return false;
      }

      // The pawn that can be captured en passant is one row "behind" the target
      int captured_index = (white_move ? to - 8 : to + 8);
      if (!board[captured_index] || !board[captured_index]->get_piece()){
        return false;
      }

      // Must be an enemy pawn
      Pawn* captured_pawn = dynamic_cast<Pawn*>(board[captured_index]->get_piece().get());
      if(!captured_pawn){
        return false;
      }

      if(captured_pawn->color == white_move){
        return false;
      }

      // The enemy pawn must have just moved two squares last turn
      if(!captured_pawn->just_moved_two){
        return false;
      }

      return true;
}
*/
    bool Board::check_en_passant(int to, int from, bool white_move) {
    int from_row = index_to_row(from);  // 0..7
    int from_col = index_to_col(from);  // 0..7
    int to_row   = index_to_row(to);
    int to_col   = index_to_col(to);

    // Must be diagonal by exactly 1 column
    if (std::abs(from_col - to_col) != 1) return false;

    // White moves up (row+1), Black moves down (row-1)
    if ((white_move && to_row - from_row != 1) ||
        (!white_move && from_row - to_row != 1)) {
        return false;
    }

    // Destination must be empty
    if (!is_on_board(to_row, to_col)) return false;
    if (board[to] && board[to]->get_piece() != nullptr) return false;

    // Captured pawn is "behind" the destination square
    int captured_index = white_move ? to - 8 : to + 8;
    if (captured_index < 0 || captured_index >= 64) return false;

    if (!board[captured_index] || !board[captured_index]->get_piece()) return false;

    // Must be an enemy pawn
    Pawn* captured_pawn = dynamic_cast<Pawn*>(board[captured_index]->get_piece().get());
    if (!captured_pawn) return false;
    if (captured_pawn->color == white_move) return false;

    // Must have just moved two squares
    if (!captured_pawn->just_moved_two) return false;

    return true;
}

/*get functions*/

    int Board::get_index(char letter, char number){
      int col =  1 + (letter -'a');
      int row = (number -'0');

      return  (((row-1)*8)+(col -1));;
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
      return (index / 8);
    }

    int Board::index_to_col(int index){
      return (index % 8);
    }

/*Sqaure functionalities*/

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