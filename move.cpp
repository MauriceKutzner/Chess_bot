#include <iostream>
#include <vector>
#include <array>
#include "board.h"

using namespace std;

enum Letter {A , B = 8, C = 16, D = 24, E = 32, F = 40, G = 48, H = 56};

//bool b_w is true if white is to move and false if black is to move

void move (array<Board::Piece, 64> board, bool b_w){

  string move_str;
  cin >> move_str;    //get the move

  if(sizeof(move_str) == 2){        //case for 2 letters notes 
    char let, num;
    let = move_str[1];        //the letter of the square
    num = move_str[2];        //the number of the square

    int index = char_to_square(let, num);

    board[index] = Board::Pawn;

    if(b_w == false){
      board[index] = Board::bPawn;
      board

    }

  }         

  else if (sizeof(move_str) == 3){         //case for 3 letters noted
    char p, let, num;
    p = move_str[0];           //the piece moved
    let = move_str[1];        //the letter of the square
    num = move_str[2];        //the number of the square

    if(islower(p)){

    }

    switch(p){
      case 'K':
      case 'Q':
      case 'R':
      case 'B':
      case 'N':
      default:

    }

  }

  else if(sizeof(move_str) == 4){     //case for 4 letters noted 
    char p, var, let, num;
    p = move_str[0];          //the piece moved
    var = move_str[1];        //x would symbolize capture, a letter or number would indicate which pice was chosen 
    let = move_str[2];        //the letter of the square
    num = move_str[3];        //the number of the square



  }

  else if(sizeof(move_str) == 5){     //case for 5 letters noted

  }

  
}

int letter_to_number(char letter){

  switch (letter){
    case 'A':
      return 0;
    case 'B':
      return 8;
    case 'C':
      return 16;
    case 'D':
      return 24;
    case 'E':
      return 32;
    case 'F':
      return 40;
    case 'G':
      return 48;
    case 'H':
      return 56;
  }
}

int char_to_square(char letter, char number){
  int a = letter_to_number(letter);

  int index = a + number - 1;       //this returns the index of the square
  return index;
}