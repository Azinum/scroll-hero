// game.c

#include <time.h>

#include "common.h"
#include "render.h"
#include "window.h"

#include "game.h"

#define TITLE_LENGTH_MAX 32

static double deltatime = 0;

int game_execute(int argc, char** argv) {
  log_out("%s\n", "Game has been initialized");
  if (window_init("Generic game | 800x600", 800, 600) != 0)
    return -1;

  clock_t time_now = 0;
  clock_t time_last = 0;
  double deltatime_max = 0.25f;

  while (!window_pollevent()) {
    time_last = time_now;
    time_now = clock();
    deltatime = ((double)(time_now - time_last)) / CLOCKS_PER_SEC;
    if (deltatime > deltatime_max)
      deltatime = deltatime_max;

    render_text(10, 10, 1, "Hello, World! This is a long string of text.");
    window_render();
    window_clear();
  }
  window_free();
  return 0;
}

double game_deltatime() {
  return deltatime;
}