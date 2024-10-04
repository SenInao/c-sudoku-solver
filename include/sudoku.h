#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdio.h>
#include <stdlib.h>

extern int SIZE_ROWS;
extern int SIZE_COLS;
extern int UNSOLVED;

typedef struct Sudoku {
  struct Square *** squares;
  struct Box ** boxes;
} Sudoku;

typedef struct Box {
  struct Square ** squares;
  int numbers;
  int possible[9];
  int solvable;
  struct Box * next;
} Box;

typedef struct Square {
  int number;
  int possible[9];
  int solvable;
  Box* box;
  int row;
  int column;
} Square;

int ** createPuzzle();
void printPuzzle(Square *** puzzle);
Sudoku * setUpPuzzle(int ** puzzle);

Sudoku * createSudoku(Square *** puzzle, Box ** boxes);

int checkPuzzle(Square *** sudoku, Box ** boxes);
int solveSquare(Square * square);
int updateSudoku(Square *** sudoku, int row, int column);
int updateBoxes(Square *** sudoku, int row, int column);

int boxSingles(Square *** sudoku, Box ** boxes);

Box ** createBoxes();

#endif
