#include "../include/sudoku.h"

int SIZE_ROWS = 9;
int SIZE_COLS = 9;
int UNSOLVED = 81;

int main() {
  int ** puzzle;
  Sudoku * sudoku;
  int progress;

  puzzle = createPuzzle();
  sudoku = setUpPuzzle(puzzle);

  printPuzzle(sudoku->squares);
  printf("\n");

  while (UNSOLVED > 0) {
    progress = checkPuzzle(sudoku->squares, sudoku->boxes);
    if (progress == 0) {
      printf("Failed to solve...\n");
      break;
    }
  }

  printPuzzle(sudoku->squares);

  return 0;
}
