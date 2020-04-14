// game.c

#include <time.h>

#include "common.h"
#include "entity.h"
#include "render.h"
#include "window.h"

#include "game.h"

#define TITLE_LENGTH_MAX 32

static double deltatime = 1;

int game_execute(int argc, char** argv) {
  log_out("%s\n", "Game has been initialized");
  if (window_init("Generic game | 800x600", 800, 600) != 0)
    return -1;
  clock_t time_now = 0;
  clock_t time_last = 0;
  double deltatime_max = 0.25f;

  struct Entity player;
  entity_default(&player);
  player.x = 40; player.y = 40; player.w = 15; player.h = 15;
  const unsigned char* state = window_keyboardstate();

  while (!window_pollevent()) {
    time_last = time_now;
    time_now = window_time();
    deltatime = ((double)(time_now - time_last)) / CLOCKS_PER_SEC;
    if (deltatime > deltatime_max)
      deltatime = deltatime_max;

    render_text(10, 10, 0.5f, "HP: 5/5");
    entity_render(&player);

    if (state[26])
      player.y -= 3;
    if (state[22])
      player.y += 3;
    if (state[4])
      player.x -= 3;
    if (state[7])
      player.x += 3;

    window_render();
    window_clear();
  }
  window_free();
  return 0;
}

double game_deltatime() {
  return deltatime;
}