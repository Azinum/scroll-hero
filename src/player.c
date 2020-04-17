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
static int16_t gravity = 1;
static int16_t jump_speed = 14;
static uint16_t super_jump_speed = 30;
struct Entity* player;
static void* texture;

void player_init() {
  player = entity_add(100, 150);
  player->flags = ENTITY_MOVABLE;
  texture = texture_load_from_file("resources/sprites/boy-8x8.png");
}

void player_update() {
  const uint8_t* state = window_keyboardstate();
  
  if (state[26] && player->grounded)  // Keycode for 'w'
    player->y_speed = -jump_speed;

  if (state[27] && player->grounded)  // 'x'
    player->y_speed = -super_jump_speed;

  if (state[4])
    player->x_speed = -player_speed;
  else if (state[7])
    player->x_speed = player_speed;
  else
    player->x_speed *= 0.5f;

  player->y_speed += gravity;
}

void player_render() {
  render_texture(player->x - camera.x, player->y - camera.y, 32, 32, texture);
}

void player_free() {
  texture_free(texture);
}
