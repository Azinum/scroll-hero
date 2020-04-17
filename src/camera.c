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
  if (
    player->x > (camera.x + (SCREEN_WIDTH * 0.90f))  ||
    player->x < (camera.x + (SCREEN_WIDTH * 0.10f))  ||
    player->y > (camera.y + (SCREEN_HEIGHT * 0.90f)) ||
    player->y < (camera.y + (SCREEN_HEIGHT * 0.10f))
  ) {
    camera.x = player->x + (-SCREEN_CENTER_X);
    camera.y = player->y + (-SCREEN_CENTER_Y);
  }
}