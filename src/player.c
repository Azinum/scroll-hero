// player.c

#include "common.h"
#include "render.h"
#include "camera.h"
#include "window.h"
#include "game.h"
#include "entity.h"

#include "player.h"

static short player_speed = 4;
static short x_speed = 0;
static short y_speed = 0;

void player_init() {
  player.x = 80;
  player.y = 150;
  player.w = 20;
  player.h = 20;
}

void player_update() {
  const unsigned char* state = window_keyboardstate();
 
  if (state[26])
    y_speed = -player_speed;
  else if (state[22])
    y_speed = player_speed;
  else {
    if (y_speed > 0)
      y_speed--;
    else if (y_speed < 0)
      y_speed++;
  }

  if (state[4])
    x_speed = -player_speed;
  else if (state[7])
    x_speed = player_speed;
  else {
    if (x_speed > 0)
      x_speed--;
    else if (x_speed < 0)
      x_speed++;
  }

  player.x += x_speed;
  player.y += y_speed;
}

void player_render() {
  render_fill_rect(player.x - camera.x, player.y - camera.y, player.w, player.h, 100, 100, 255, 255);
}