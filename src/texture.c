// texture.c -- image -> SDL_Texture

#include <SDL2/SDL.h>
#include <assert.h>

#include "image.h"
#include "window.h"
#include "texture.h"

static void* texture_from_image(struct Image* image);

void* texture_from_image(struct Image* image) {
  assert(image != NULL);
  void* texture;
  // TODO: Add big-endian support (for the color masks)
  SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(
    image->pixel_buffer,
    image->width,
    image->height,
    32, // Depth seems to be invalid here (image->depth)
    image->pitch,
    0x000000ff,
    0x0000ff00,
    0x00ff0000,
    0xff000000
  );
  texture = SDL_CreateTextureFromSurface(window_renderer(), surface);
  return texture;
}

void* texture_load_from_file(const char* path) {
  void* texture = NULL;
  struct Image image;
  image_load_png(path, &image);
  texture = texture_from_image(&image);
  image_free_pixel_buffer(image.pixel_buffer);
  return texture;
}

void texture_free(void* texture) {
  assert(texture != NULL);
  SDL_DestroyTexture(texture);
}