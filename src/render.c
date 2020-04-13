// render.c

#include <SDL2/SDL.h>

#include "common.h"
#include "window.h"
#include "render.h"

void render_rect(int x, int y, int w, int h, int r, int g, int b, int a) {
  SDL_Renderer* renderer = window_renderer();
  assert(renderer != NULL);
  const SDL_Rect rect = {
    x, y, w, h
  };
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
  SDL_RenderDrawRect(renderer, &rect);
}

void render_fill_rect(int x, int y, int w, int h, int r, int g, int b, int a) {
  SDL_Renderer* renderer = window_renderer();
  assert(renderer != NULL);
  const SDL_Rect rect = {
    x, y, w, h
  };
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
  SDL_RenderFillRect(renderer, &rect);
}