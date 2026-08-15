#include "board.h"
#include <stdlib.h>
#include <wchar.h>

/*
    init the board using width and height,
    use calloc to allocate memory with every byte set to 0
    (malloc does not init the allocated memory, behavior may be unexpected)
 */
Board board_create(int width, int height) {
  Board b;
  b.width = width;
  b.height = height;
  b.cells = calloc(width * height, sizeof(bool));
  return b;
}
/*
    destroy the board by freeing it from memory and setting all the cells to NULL.
 */
void board_destroy(Board *board) {
  free(board->cells);
  board->cells = NULL;
}

/*
    determines whether given x and y are within the proper bounds
 */
static inline bool is_in_bounds(const Board *board, int x, int y) {
    return (x >= 0 && x < board->width && y >= 0 && y < board->height);
}

/*
    uses helper function is_in_bounds();
    since memory is 1D, we need to convert the 2D index to 1D using:
    index = y * width + x;
 */
bool board_get(Board *board, int x, int y) {
  if (!is_in_bounds(board, x, y)) return false;
  return board->cells[y * board->width + x];
}

/*
    function for setting a specific cell to given input state
 */
void board_set(Board *board, int x, int y, bool state) {
  board->cells[y * board->width + x] = state;
}
/*
    function for counting a cell's neighbours.

            -1        0        1
       -1 [-1, -1] [-1, 0] [-1, 1]
        0 [ 0, -1] [ 0, 0] [ 0, 1]
        1 [ 1, -1] [ 1, 0] [ 1, 1]

       [0, 0] is cell itself. => if x == 0 && y == 0 continue;
 */
int count_neighbours(const Board *board, int x, int y) {
  int counter = 0;

  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {

      // if cell itself then continue
      if (i == 0 && j == 0) continue;

      /*
        Example:
            x = 3; y = 3;     board_get(board, 3 + (-1), 3 + (-1)) ->
                                        board_get(board, 2, 2);

            3 - 1     3     3 + 1
       3-1 [3-1, 3-1] [3-1, 3] [3-1, 3+1]
        3  [3,   3-1] [3,   3] [3,   3+1]
       3+1 [3+1, 3-1] [3+1, 3] [3+1, 3+1]

       using <stdbool.h>, booleans are evaluated to 1 and 0 if added onto an int

       */

      counter += board_get(board, x + i, y + j);
    }
  }
  return counter;
}

/*
    helper function to evaluate which state too choose for next step
 */
bool eval_cell(int n, bool state) {

  if (state) {
    if (n < 2) {
      // cell dies -> underpopulation
      return false;
    } else if (n > 3) {
      // cell dies -> overpopulation
      return false;
    } else if (n == 2 || n == 3) {
      // cell survives
      return true;
    }

  } else {
    if (n == 3) {
      // reproduction
      return true;
    }
  }
  return false;
}

/*
    simulates 1 step of the board
 */
void board_step(Board *board) {

  // second copy board, needed for double-buffer
  Board next = board_create(board->width, board->height);

  for (int y = 0; y < board->height; y++) {
    for (int x = 0; x < board->width; x++) {
      bool alive = board_get(board, x, y);
      int n = count_neighbours(board, x, y);

      bool next_state = eval_cell(n, alive);
      board_set(&next, x, y, next_state);
    }
}

  free(board->cells);
  // copy cells from copy-board over
  board->cells = next.cells;
}
