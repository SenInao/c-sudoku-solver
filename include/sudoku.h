#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Box {
  struct Box * next;
} Box;

typedef struct Square {
  int number;
  int possible[9];
  Box* box;
  int row;
  int column;
} Square;

int ** createPuzzle();
void printPuzzle();
Square *** setUpPuzzle();

#endif
