// game.c

#include <time.h>

#include "common.h"
#include "camera.h"
#include "entity.h"
#include "player.h"
#include "hud.h"
#include "render.h"
#include "window.h"

#include "game.h"

#define TITLE_LENGTH_MAX 32

static double deltatime = 1;
static double totaltime = 0;

int game_execute(int argc, char** argv) {
  log_out("%s\n", "Game has been initialized");
  if (window_init("Generic game | 800x600", 800, 600) != 0)
    return -1;

  camera_init();
  player_init();

  entity_add(50, 140);
  entity_add(150, 230);

  double time_now = 0;
  double time_last = 0;
  const double deltatime_max = 0.25f;

  while (!window_pollevent()) {
    time_last = time_now;
    time_now = window_time();
    deltatime = ((double)(time_now - time_last)) / (CLOCKS_PER_SEC * 1000);
    if (deltatime > deltatime_max)
      deltatime = deltatime_max;
    totaltime += deltatime;

    camera_update();
    entities_update();
    player_update();

    entities_render();
    player_render();

    hud_render(); // Render HUD on top of everything

    window_render();
    window_clear();
  }
  entities_clear(entities);
  window_free();
  return 0;
}

double game_deltatime() {
  return deltatime;
}

double game_totaltime() {
  return totaltime;
}