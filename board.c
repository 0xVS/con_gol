#include "board.h"
#include <stdlib.h>

/*
    init the board using width and height,
    use calloc to allocate memory with every byte set to 0
    (malloc does not init the allocated memory, behavior may be unexpected)
 */
Board board_create(int width, int height) {
  Board b;
  b.width = width;
  b.height = height;
  b.cells = calloc(width*height, sizeof(bool));
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
  if (is_in_bounds(board, x, y)) {
    return board->cells[y * board->width + x];
  } else
}

void board_set(Board *board, int x, int y, bool state) {
  board->cells[y * board->width + x]
}

void board_step(Board *board) {}

/*
            0      1     2
       0 [0, 0] [0, 1] [0, 2]
       1 [1, 0] [1, 1] [1, 2]
       2 [2, 0] [2, 1] [2, 2]

       [1, 1] is cell itself. => if x == 1 && y == 1 continue;
 */
int count_neighbours(Board *board, int x, int y) {
  int counter = 0;
  for (;;){}
}
