// player.c

#include "common.h"
#include "render.h"
#include "camera.h"
#include "window.h"
#include "texture.h"
#include "game.h"
#include "entity.h"

#include "player.h"

static short player_speed = 4;
static short x_speed = 0;
static short y_speed = 0;
static void* texture;

void player_init() {
  player.x = 80;
  player.y = 150;
  texture = texture_load_from_file("resources/sprites/boy.png");
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
  render_texture(player.x - camera.x, player.y - camera.y, 40, 40, texture);
}

void player_free() {
  texture_free(texture);
}
