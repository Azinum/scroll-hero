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
struct Entity* player;
static void* texture;

void player_init() {
  player = entity_add(80, 150);
  player->type = ENTITY_MOVABLE;
  texture = texture_load_from_file("resources/sprites/boy.png");
}

void player_update() {
  const uint8_t* state = window_keyboardstate();
 
  if (state[26])
    player->y_speed = -player_speed;
  else if (state[22])
    player->y_speed = player_speed;
  else
    player->y_speed *= 0.5f;

  if (state[4])
    player->x_speed = -player_speed;
  else if (state[7])
    player->x_speed = player_speed;
  else
    player->x_speed *= 0.5f;
}

void player_render() {
  render_texture(player->x - camera.x, player->y - camera.y, 32, 32, texture);
}

void player_free() {
  texture_free(texture);
}
