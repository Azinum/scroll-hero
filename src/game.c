// game.c

#include "shared.h"
#include "window.h"

#include "game.h"

int game_execute(int argc, char** argv) {
  log_out("%s\n", "Game has been initialized");
  if (window_init("Generic game | 800x600", 800, 600) != 0)
    return -1;

  while (!window_pollevent()) {
    window_render();
    window_clear();
  }
  window_free();
  return 0;
}