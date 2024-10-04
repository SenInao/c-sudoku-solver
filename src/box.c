#include "../include/sudoku.h"
#include <stdlib.h>

Box ** createBoxes() {
  Box ** boxes;

  boxes = malloc(sizeof(Box*)*SIZE_ROWS);

  for (int i = 0; i<9; i++) {
    boxes[i] = malloc(sizeof(Box));
    boxes[i]->squares = malloc(sizeof(Square*) * 9);
    boxes[i]->numbers = 0;
    boxes[i]->solvable = 9;

    for (int j = 0; j<9; j++) {
      boxes[i]->possible[j] = 0;
    }
  }

  return boxes;
}

int updateBoxes(Square *** sudoku, int row, int column) {
  int x;
  int number = sudoku[row][column]->number;
  Box * box = sudoku[row][column]->box;

  for (x = 0; x < 9; x++) {
    if (box->squares[x]->possible[number - 1] == 0) {
      box->squares[x]->solvable--;
    }
    box->squares[x]->possible[number - 1] = 1;
  }

  return 1;
};

int boxSingles(Square *** sudoku, Box ** boxes) {
  int i, j, x;
  int count;
  int temp;

  for (i = 0; i<9; i++) {
    for (j = 0; j<9; j++) {
      count = 0;

      for (x = 0; x < 9; x++) {
        if (boxes[i]->squares[x]->number != 0) {
          continue;
        }
        if (boxes[i]->squares[x]->possible[j] == 0) {
          count ++;
          temp = x;
        }
        if (count == 2) {
          break;
        }
      }

      if (count == 1) {
        boxes[i]->squares[temp]->number = j+1;
        UNSOLVED--;
        boxes[i]->squares[temp]->solvable = 0;

        updateSudoku(sudoku, boxes[i]->squares[temp]->row, boxes[i]->squares[temp]->column);

        return 1;
      }
    }
  }

  return 0;
}
