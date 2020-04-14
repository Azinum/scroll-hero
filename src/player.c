// player.c

#include "common.h"
#include "render.h"
#include "camera.h"
#include "window.h"
#include "game.h"
#include "entity.h"

#include "player.h"

static float player_speed = 50.0f;
static float player_maxspeed = 300.0f;
static float x_vel = 0;
static float y_vel = 0;

void player_init() {
  player.x = 80;
  player.y = 150;
  player.w = 20;
  player.h = 20;
}

void player_update() {
  const unsigned char* state = window_keyboardstate();
 
  if (state[26])
    y_vel -= player_speed;
  if (state[22])
    y_vel += player_speed;

  if (state[4])
    x_vel -= player_speed;
  if (state[7])
    x_vel += player_speed;

  if (y_vel > 0 && y_vel > player_maxspeed)
    y_vel = player_maxspeed;
  else if (y_vel < 0 && y_vel < -player_maxspeed)
    y_vel = -player_maxspeed;

  if (x_vel > 0 && x_vel > player_maxspeed)
    x_vel = player_maxspeed;
  else if (x_vel < 0 && x_vel < -player_maxspeed)
    x_vel = -player_maxspeed;

  player.x += x_vel * game_deltatime();
  player.y += y_vel * game_deltatime();
}

void player_render() {
  render_fill_rect(player.x - camera.x, player.y - camera.y, player.w, player.h, 100, 100, 255, 255);
}