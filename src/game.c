// game.c

#include <time.h>

#include "common.h"
#include "camera.h"
#include "render.h"
#include "window.h"
#include "entity.h"
#include "tables.h"
#include "player.h"
#include "hud.h"

#include "game.h"

#define TITLE_LENGTH_MAX 32
#define TILE_SIZE 32

double deltatime = 0;
double totaltime = 0;
int16_t game_tick = 0;

static void game_init() {
  // srand(time(NULL));
  int32_t seed = 55102;
  srand(seed);
  camera_init();
  player_init();

  for (uint32_t i = 5; i < 10; i++) {
    int32_t x = i * TILE_SIZE;
    int32_t y = 400;
    entity_add(x - (x % TILE_SIZE), y - (y % TILE_SIZE), ENTITY_MONSTER);
  }

  for (uint32_t i = 0; i < 150; i++) {
    int32_t x = rand() % 1500;
    int32_t y = rand() % 364;
    struct Entity* e = entity_add(x - (x % TILE_SIZE), y - (y % TILE_SIZE), ENTITY_MONSTER);
    e->flags |= FLAGS_STATIC;
  }

  for (uint32_t i = 0; i < 80; i++) {
    struct Entity* e = entity_add(i * TILE_SIZE, 450, -1);
    e->flags |= FLAGS_STATIC | FLAGS_COLLIDABLE;
  }
}

int game_execute(int argc, char** argv) {
  log_printf("%s\n", "Game has been initialized");
  if (window_init("Scroll Hero | 800x600", SCREEN_WIDTH, SCREEN_HEIGHT) != 0)
    return -1;

  game_init();
  double time_now = 0;
  double time_last = 0;
  double deltatime_max = 20.0f;

  while (!window_pollevent()) {
    game_tick++;
    time_last = time_now;
    time_now = window_time();
    deltatime = (time_now - time_last) / (CLOCKS_PER_SEC);
    if (deltatime > deltatime_max)
      deltatime = deltatime_max;
    totaltime += deltatime;

    player_update();
    entities_update();
    camera_update();

    entities_render();
    player_render();

    hud_render(); // Render HUD on top of everything

    window_render();
    window_clear();
  }
  entities_clear(entities);
  player_free();
  window_free();
  return 0;
}
