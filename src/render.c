// render.c

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "common.h"
#include "texture.h"
#include "window.h"
#include "render.h"

static void* temp_texture;

void render_rect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, int32_t g, int32_t b, int32_t a) {
  SDL_Renderer* renderer = window_renderer();
  assert(renderer != NULL);
  const SDL_Rect rect = {
    x, y, w, h
  };
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
  SDL_RenderDrawRect(renderer, &rect);
}

void render_fill_rect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, int32_t g, int32_t b, int32_t a) {
  SDL_Renderer* renderer = window_renderer();
  assert(renderer != NULL);
  const SDL_Rect rect = {
    x, y, w, h
  };
  SDL_SetRenderDrawColor(renderer, r, g, b, a);
  SDL_RenderFillRect(renderer, &rect);
}

void render_text(int32_t x, int32_t y, float size, const char* text) {
  assert(window_font() != NULL);
  int32_t width = 0;
  int32_t height = 0;
  SDL_Renderer* renderer = window_renderer();
  SDL_Surface* surface = TTF_RenderText_Blended(window_font(), text, (struct SDL_Color) {255, 255, 255, 255});
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_QueryTexture(texture, NULL, NULL, &width, &height);
  SDL_Rect destination = {x, y, (int32_t)(size * width), (int32_t)(size * height)};
  SDL_RenderCopy(renderer, texture, NULL, &destination);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}

void render_texture(int32_t x, int32_t y, int32_t w, int32_t h, void* texture) {
  // assert(texture != NULL);
  if (!temp_texture) {
    temp_texture = texture_load_from_file("resources/sprites/tile-brick.png");
  }
  if (!texture) {
    texture = temp_texture;
  }
  SDL_Renderer* renderer = window_renderer();
  SDL_Rect rect = (struct SDL_Rect) {x, y, w, h};
  SDL_RenderCopy(renderer, texture, NULL, &rect);
#if 0
  render_rect(x, y, w, h, 255, 50, 50, 255);
#endif
}