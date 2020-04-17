// camera.c

#include "common.h"
#include "player.h"
#include "camera.h"

void camera_init() {
  camera.x = 0;
  camera.y = 0;
}

void camera_update() {
  if (!player)
    return;

  if (player->y > (camera.y + (SCREEN_HEIGHT * 0.90f)) ||
      player->y < (camera.y + (SCREEN_HEIGHT * 0.10f))) {
    camera.y = player->y + (-SCREEN_CENTER_Y);
  }

  if (player->x > (camera.x + (SCREEN_WIDTH * 0.6f)))
    camera.x = player->x + (-(SCREEN_WIDTH) * 0.6f);

  if (player->x < (camera.x + (SCREEN_WIDTH * 0.4f)))
    camera.x = player->x + (-(SCREEN_WIDTH) * 0.4f);
}