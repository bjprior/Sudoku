/*               Presupplied functions                        */

void load_board(const char* filename, char board[9][9]);

void display_board(const char board[9][9]);

/*                 functions created                     */ 

/* function to check whether the board loaded has been completed or not */
bool is_complete(const char board[9][9]);

/* function to place a given digit to a position on the sudoku board */

bool make_move(const char position[10], char digit, char board[9][9]);

/* function to save a board to a new file with a given filename */

bool save_board(const char filename[13], const char board[9][9]);

/* function to solve the sudoku board */

bool solve_board(char board[9][9]);


