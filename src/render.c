// render.c

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

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

void render_text(int x, int y, float size, const char* text) {
  assert(window_font() != NULL);
  int width = 0;
  int height = 0;
  SDL_Renderer* renderer = window_renderer();
  SDL_Surface* surface = TTF_RenderText_Blended(window_font(), text, (struct SDL_Color) {255, 255, 255, 255});
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_QueryTexture(texture, NULL, NULL, &width, &height);
  SDL_Rect destination = {x, y, (int)(size * width), (int)(size * height)};
  SDL_RenderCopy(renderer, texture, NULL, &destination);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}

void render_texture(int x, int y, int w, int h, void* texture) {
  assert(texture != NULL);
  SDL_Renderer* renderer = window_renderer();
  SDL_Rect rect = (struct SDL_Rect) {x, y, w, h};
  SDL_RenderCopy(renderer, texture, NULL, &rect);
#if 1 // Debug
  render_rect(x, y, w, h, 255, 50, 50, 255);
#endif
}