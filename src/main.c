// main.c

#include "image.h"
#include "common.h"
#include "game.h"

int main(int argc, char** argv) {
  struct Image image;
  image_load_png("resources/sprites/boy.png", &image);
  printf("w: %i, h: %i, depth: %i, pitch: %i\n", image.width, image.height, image.depth, image.pitch);
  image_free_pixel_buffer(image.pixel_buffer);
  return 0; // return game_execute(argc, argv);
}