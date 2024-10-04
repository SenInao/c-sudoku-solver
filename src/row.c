#include "../include/sudoku.h"
#include <stdio.h>

int checkRows(Square *** sudoku) {
  int x, j, k;
  int sum[9];
  int place[9];

  for (x = 0; x < SIZE_ROWS; x++) {

    for (j = 0; j < 9; j++) {
      sum[j] = 0;
      place[j] = 0;
    }

    for (j = 0; j < 9; j++) {
      if (sudoku[x][j]->number != 0) {
        continue;
      }

      for (k = 0; k < 9; k++) {
        if (sudoku[x][j]->possible[k] == 0) {
          sum[k]++;
          place[k] = j;
        }
      }
    }

    for (j = 0; j < 9; j++) {
      if (sum[j] == 1) {
        sudoku[x][place[j]]->number = j + 1;
        sudoku[x][place[j]]->solvable = 0;
        UNSOLVED--;
        updateSudoku(sudoku, x, place[j]);
        updateBoxes(sudoku, x, place[j]);
        return 1;
      }
    }
  }

  return 0;
}
