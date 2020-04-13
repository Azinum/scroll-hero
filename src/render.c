// render.c

#include "shared.h"
#include "window.h"
#include "render.h"

#include <SDL2/SDL.h>

void render_rect(int x, int y, int w, int h, int r, int g, int b, int a) {
  SDL_Renderer* renderer = window_renderer();
  assert(renderer != NULL);
  const SDL_Rect rect = {
    x, y, w, h
  };
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
  SDL_RenderDrawRect(renderer, &rect);
}