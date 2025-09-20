#include "sudoku.h"
//Introduction Paragraph
/*
*Parnter: anara32
*This program implmements a sudoku solver using the recursive backtracking algorithim
*the implementation follows these key steps
*1.Find an empty cell in the Sudoku grid
*2. Try placing digits from 1-9 in that cell
*3. For each digit, check if its valid according to sudoku rules
*4. If valid, place the digit and recurisvely solve the rest of the puzzle
*5. If the recursive call fails, backtrack by undoing the placement
*this approach uses recursion to systematically check all possibilities until a solution is found
*/
//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------
// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {
  assert(i>=0 && i<9);
  // BEG TODO
  //Iterate through all columns in row i 
  for (int j = 0; j < 9; j++) {
    //check if the value exists in this position
    if (sudoku[i][j] == val) {
      return 1; // Value found in row
    }
  }
  return 0; // Value not found in row
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {
  assert(j>=0 && j<9);
  // BEG TODO
  //iterate through all rows in column j 
  for (int i = 0; i < 9; i++) {
    //check if value exists in this position
    if (sudoku[i][j] == val) {
      return 1; // Value found in column
    }
  }
  return 0; // Value not found in column
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
  assert(i>=0 && i<9);
  assert(j>=0 && j<9);
  
  // BEG TODO
  // Find the top-left corner of the 3x3 zone
  //Calculate the top-left corner of the 3x3 zone that contains cell (i, j)
  //dividing by 3 gives us the zone index(0,1,2)
  //multiplying by 3 gives us the starting index of that zone
  int zone_row = (i / 3) * 3;
  int zone_col = (j / 3) * 3;
  
  // Check all cells in the 3x3 zone
  for (int r = zone_row; r < zone_row + 3; r++) {
    for (int c = zone_col; c < zone_col + 3; c++) {
      if (sudoku[r][c] == val) {
        return 1; // Value found in 3x3 zone
      }
    }
  }
  return 0; // Value not found in 3x3 zone
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {
  assert(i>=0 && i<9 && j>=0 && j<9);
  // BEG TODO
  //A value is valid if it doesnt violate any of the three sudoku constraints
  if (!is_val_in_row(val, i, sudoku) && 
      !is_val_in_col(val, j, sudoku) && 
      !is_val_in_3x3_zone(val, i, j, sudoku)) {
    return 1; // Valid placement
  }
  return 0; // Invalid placement
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {
  // BEG TODO.
  int row = -1;
  int col = -1;
  int isEmpty = 0;
  
  // Find an empty cell (containing 0)
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (sudoku[i][j] == 0) {
        //remember the position of the empty cell 
        row = i;
        col = j;
        isEmpty = 1;
        break;
      }
    }
    if (isEmpty) {
      //exit the outer loop 
      break;
    }
  }
  
  // If no empty cell is found, puzzle is solved
  if (!isEmpty) {
    return 1;
  }
  
  // Try placing digits 1-9 in the empty cell
  for (int num = 1; num <= 9; num++) {
    // Check if it's safe to place the digit
    if (is_val_valid(num, row, col, sudoku)) {
      // Place the digit
      sudoku[row][col] = num;
      
      // Recursively solve the rest of the puzzle
      if (solve_sudoku(sudoku)) {
        return 1; // If successful, return true
      }
      
      // If placing the digit didn't lead to a solution, backtrack
      sudoku[row][col] = 0;
    }
  }
  
  // No solution exists
  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}