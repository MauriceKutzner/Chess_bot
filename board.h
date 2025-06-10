#pragma once
#include <array>


  class Board{
    public:
      enum Piece_type {King, Queen, Rook, Bishop, Knight, Pawn, bKing, bQueen, bRook, bBishop, bKnight, bPawn,Empty};

      Board();
      void fill_board();
      void print_board();

      std::array<Piece_type, 64> board;

  };

