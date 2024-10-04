#include "../include/sudoku.h"
#include <stdlib.h>

Sudoku * createSudoku(Square *** squares, Box ** boxes) {
  Sudoku * sudoku;

  sudoku = malloc(sizeof(Sudoku));

  sudoku->squares = squares;
  sudoku->boxes = boxes;

  return sudoku;
}

int updateSudoku(Square *** sudoku, int row, int column) {
  int x;
  int number = sudoku[row][column]->number;

  for (x = 0; x < SIZE_ROWS; x++) {
    if (sudoku[x][column]->possible[number - 1] == 0) {
      sudoku[x][column]->solvable--;
    }
    sudoku[x][column]->possible[number-1] = 1;
  }

  for (x = 0; x < SIZE_COLS; x++) {
    if (sudoku[row][x]->possible[number - 1] == 0) {
      sudoku[row][x]->solvable--;
    }
    sudoku[row][x]->possible[number-1] = 1;
  }

  return 1;
}

Sudoku * setUpPuzzle(int ** puzzle) {
  Box ** boxes;
  Square *** sudoku;
  int i, j;
  int currBox = 0;

  sudoku = malloc(sizeof(Square**)*9);

  boxes = createBoxes();



  for (i = 0; i < SIZE_ROWS; i++) {
    sudoku[i] = malloc(sizeof(Square*)*9);

    for (j = 0; j < SIZE_COLS; j++) {
      sudoku[i][j] = malloc(sizeof(Square)*9);

      sudoku[i][j] -> number = puzzle[i][j];
      sudoku[i][j]->row=i;
      sudoku[i][j]->column=j;
      sudoku[i][j]->solvable=9;

      boxes[currBox]->squares[boxes[currBox]->numbers] = sudoku[i][j];
      sudoku[i][j]->box = boxes[currBox];
      boxes[currBox]->numbers++;

      for (int d = 0; d < SIZE_COLS; d++) {
        sudoku[i][j]->possible[d] = 0;
      }

      if (j == 2 || j == 5) {
        currBox++;
      }
    }

    currBox -= 2;
    if (i == 2 || i == 5) {
      currBox+=3;
    }
  }

  for (i = 0; i < SIZE_ROWS; i++) {
    for (j = 0; j < SIZE_COLS; j++) {
      if (sudoku[i][j]->number != 0) {
        sudoku[i][j]->solvable = 0;
        sudoku[i][j]->box->possible[sudoku[i][j]->number] = 0;
        updateSudoku(sudoku, i, j);
        updateBoxes(sudoku, i, j);
        UNSOLVED--;
      }
    }
  }

  return createSudoku(sudoku, boxes);
}

int checkPuzzle(Square *** sudoku, Box ** boxes) {
  int i, j, x;

  for (i = 0; i < SIZE_ROWS; i++) {
    for (j = 0; j < SIZE_COLS; j++) {
      if (sudoku[i][j]->solvable == 1) {
        solveSquare(sudoku[i][j]);
        updateSudoku(sudoku, i, j);
        updateBoxes(sudoku, i, j);

        return 1;
      }
    }
  }

  return boxSingles(sudoku, boxes);
}

int ** createPuzzle() {
  int ** puzzle;
  int i, j;
  int array[9][9] = {0, 1, 9,   0, 0, 2,  0, 0, 0,
                     4, 7, 0,   6, 9, 0,  0, 0, 1,
                     0, 0, 0,   4, 0, 0,  0, 9, 0,

                     8, 9, 4,   5, 0, 7,  0, 0, 0,
                     0, 0, 0,   0, 0, 0,  0, 0, 0,
                     0, 0, 0,   2, 0, 1,  9, 5, 8,

                     0, 5, 0,   0, 0, 6,  0, 0, 0,
                     6, 0, 0,   0, 2, 8,  0, 7, 9,
                     0, 0, 0,   1, 0, 0,  8, 6, 0};

  puzzle = malloc(sizeof(int*)*9);

  for (i = 0; i < SIZE_ROWS; i++) {
    puzzle[i] = (int*)malloc(sizeof(int)*9);

    for (j = 0; j < SIZE_COLS; j++) {
      puzzle[i][j] = array[i][j];
    }
  }

  return puzzle;
}

void printPuzzle(Square *** puzzle) {
  int i, j;

  printf("-------------------------------\n");
  for (i = 0; i<SIZE_ROWS; i++) {
    printf("|");

    for (j = 0; j<SIZE_COLS; j++) {
      printf(" %d ", puzzle[i][j]->number);

      if ((j+1) % 3 == 0) {
        printf("|");
      }
    }
    printf("\n");
    if ((i+1) % 3 == 0) {
      printf("-------------------------------\n");
    }
  }
}
