// camera.c

#include <SDL2/SDL.h>

#include "window.h"
#include "camera.h"

void camera_init() {
  camera.x = 0;
  camera.y = 0;
}

void camera_update() {
  const unsigned char* state = window_keyboardstate();
  if (state[26])
    camera.y -= 3;
  if (state[22])
    camera.y += 3;
  if (state[4])
    camera.x -= 3;
  if (state[7])
    camera.x += 3;
}