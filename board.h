#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

typedef struct {
  int width, height;
  // cells as a flat array: total size of WxH
  bool *cells;
} Board;

Board board_create(int width, int height);
// passing in pointer to struct rather than struct itself
void board_destroy(Board *board);

// get state of specific cell x, y
bool board_get(Board *board, int x, int y);
void board_set(Board *board, int x, int y, bool state);
void board_step(Board *board);

#endif
