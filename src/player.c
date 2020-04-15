// player.c

#include "common.h"
#include "render.h"
#include "camera.h"
#include "window.h"
#include "texture.h"
#include "game.h"
#include "entity.h"

#include "player.h"

static int16_t player_speed = 6;
static int16_t x_speed = 0;
static int16_t y_speed = 0;
static void* texture;

void player_init() {
  player.x = 80;
  player.y = 150;
  texture = texture_load_from_file("resources/sprites/boy.png");
}

void player_update() {
  const uint8_t* state = window_keyboardstate();
 
  if (state[26])
    y_speed = -player_speed;
  else if (state[22])
    y_speed = player_speed;
  else
    y_speed *= 0.5f;

  if (state[4])
    x_speed = -player_speed;
  else if (state[7])
    x_speed = player_speed;
  else
    x_speed *= 0.5f;

  player.x += x_speed;
  player.y += y_speed;
}

void player_render() {
  render_texture(player.x - camera.x, player.y - camera.y, 32, 32, texture);
}

void player_free() {
  texture_free(texture);
}
