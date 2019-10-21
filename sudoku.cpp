#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << '\n';
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << '\n';
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << '\n';
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << '\n';
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* functions created  */

/* function to check whether the board loaded is complete or not */

bool is_complete(const char board[9][9]){

  for(int i = 0; i <9; i++)
    for(int j= 0; j <9; j++)
      if(static_cast<int>(board[i][j]) < 49 || static_cast<int>(board[i][j]) >57 )
	return 0;

  return 1;
}

/* fucntion to check if a move is valid, makes move if valid */

bool make_move(const char position[10], char digit, char board[9][9]){

  int column, row;
  int boxcolumn, boxrow;
  char *ptr = &board[8][8];
  
  // Converts string into digits for grid and if lowercase for letter, accounts for this // 
  if(static_cast<int>(position[0]) > 96 && static_cast<int>(position[0]) < 106)
    row = static_cast<int>(position[0])- 96;
  else
    row = static_cast<int>(position[0])-64;

  column = static_cast<int>(position[1])-48;
  
  // Calculates which third of the board to check (0,1,2)//
  boxcolumn = (column-1) / 3;
  boxrow =(row-1)/3;
  
  // Checks for valid coordinate, not already filled and valid digit // 
  if(row > 9 || column > 9)
    return 0;
  if (strlen(position)>2)
    return 0;
  if(board[row -1][column -1] != '.')
    return 0;
  if (static_cast<int>(digit) < 49 || static_cast<int>(digit) > 57)
    return 0;
  
  // Check the column //
  for (int i =0; i < 9; i++){
    if (digit == board[i][column-1])
      return 0;
  }

  // Check the row //
  for (int i = 0; i < 9; i++){
    if (digit == board[row-1][i])
      return 0;
  }	
  // Check the box //
  for (int i = 3*boxcolumn; i < 3*(1+boxcolumn); i++){
    for (int j = 3*boxrow; j < 3*(1+boxrow); j++){
      if(digit == board[j][i])
	return 0;
    }
  }
  // Edits the value of desired cell if valid //
  ptr = &board[row-1][column-1];
  *ptr= digit;
  
  return 1; 
}

/* function to save a board to a new file with a given filename */

bool save_board(const char filename[13],const char board[9][9]){

  ofstream out_stream;

  // Open outstream and exit function if fail //
  out_stream.open(filename);
  if(out_stream.fail())
    return 0;

  // Copies array to the output stream //
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      out_stream << board[i][j];  
    }
    out_stream << endl;
  }
  out_stream.close();
  return 1;
}

// function to solve soduku board //

bool solve_board(char board[9][9]){

  char position [2];
  char *ptr = &board[8][8];

  static int recursive_calls = 0;
  recursive_calls ++;

  /* The outputs the number of calls to the function and resets counter to 0 when printed */
  
  if(is_complete(board)){
    cout << endl << "total calls: " << recursive_calls << endl <<endl; 
    recursive_calls = 0;
    return true;
  }
  
  for (int i =0; i <9; i++){                       //rows
    for (int j=0; j<9;j++){                       //columns   
      for (int digit= 1; digit < 10; digit++){
	position[0] = static_cast<char>(i+65);
	position[1] = static_cast<char>(j+49);
	if(make_move(position,static_cast<char>(digit+48),board)){
	  if (solve_board(board))
	    return true;
	  else{
	    ptr = &board[i][j];
	    *ptr= '.';
	  }
	}
	if(digit ==9 && board[i][j]== '.')
	  return false;
      }
    }
  }
  return 0;
}

 
	









