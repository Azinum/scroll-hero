// game.c

#include "shared.h"
#include "render.h"
#include "window.h"

#include "game.h"

#define TITLE_LENGTH_MAX 32

int game_execute(int argc, char** argv) {
  log_out("%s\n", "Game has been initialized");
  if (window_init("Generic game | 800x600", 800, 600) != 0)
    return -1;
  char title[TITLE_LENGTH_MAX] = {0};
  int i = 0;
  while (!window_pollevent()) {
    i++;
    if (!(i % 10)) {
      snprintf(title, TITLE_LENGTH_MAX, "Generic game (%i)", i);
      window_change_title(title);
    }
    render_rect(20, 20, 50, 50, 250, 100, 120, 255);
    window_render();
    window_clear();
  }
  window_free();
  return 0;
}