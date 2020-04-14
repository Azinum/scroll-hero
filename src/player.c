// player.c

#include "common.h"
#include "render.h"
#include "camera.h"
#include "window.h"
#include "entity.h"

#include "player.h"

void player_init() {
  player.x = 80;
  player.y = 80;
  player.w = 20;
  player.h = 20;
}

void player_update() {
  const unsigned char* state = window_keyboardstate();
  if (state[26])
    player.y -= 3;
  if (state[22])
    player.y += 3;
  if (state[4])
    player.x -= 3;
  if (state[7])
    player.x += 3;
}

void player_render() {
  render_fill_rect(player.x - camera.x, player.y - camera.y, player.w, player.h, 100, 100, 255, 255);
}