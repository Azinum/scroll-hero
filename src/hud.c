// hud.c

#include "common.h"
#include "game.h"
#include "player.h"
#include "camera.h"
#include "render.h"
#include "hud.h"

#define BUFFER_LENGTH 64
#define FONT_HEIGHT 25

static char text_buff[BUFFER_LENGTH] = {0};

#define INSPECT(x, y, font_size, fmt, ...) { \
  snprintf(text_buff, BUFFER_LENGTH, fmt, ##__VA_ARGS__); \
  render_text(x, y, font_size, text_buff); \
} \

void hud_render() {
  INSPECT(10, 10 + (0 * FONT_HEIGHT), 0.5f, "camera.x = %i, camera.y = %i", camera.x, camera.y);
  INSPECT(10, 10 + (1 * FONT_HEIGHT), 0.5f, "player.x = %i, player.y = %i", player.x, player.y);
  INSPECT(10, 10 + (2 * FONT_HEIGHT), 0.5f, "fps: %i, dt: %.3g", (int)(1.0f / game_deltatime()), game_deltatime());
}