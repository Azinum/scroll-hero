// player.c

#include "entity_common.h"
#include "render.h"
#include "texture.h"
#include "player.h"

static int16_t player_speed = 4;
static int16_t gravity = 1;
static int16_t jump_speed = 10;
static int16_t max_speed = 20;
static uint16_t super_jump_speed = 20;
struct Entity* player;
static void* texture;

void player_init() {
  player = entity_add(100, 300, ENTITY_PLAYER);
  player->flags = FLAGS_COLLIDABLE;
  texture = texture_load_from_file("resources/sprites/boy-with-helm.png");
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

  if (!(game_tick % 2))
    player->y_speed += gravity;

  if (player->y_speed > 0 && player->y_speed > max_speed)
    player->y_speed = max_speed;

  if (player->y_speed < 0 && player->y_speed < -max_speed)
    player->y_speed = -max_speed;
}

void player_render() {
  render_texture(player->x - camera.x, player->y - camera.y, 32, 32, texture);
}

void player_free() {
  texture_free(texture);
}
