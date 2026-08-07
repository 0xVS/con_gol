#include <stdio.h>
#include "raylib.h"

int main(void) {
  InitWindow(800, 450, "conways game of life");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    // DrawText(const char *text, int posX, int posY, int fontSize, Color color)
    DrawText(
        "first raylib window test!",
        190,
        200,
        20,
        LIGHTGRAY
    );
    EndDrawing();
  }
  printf("[info] drawing succeded!\n");
}
