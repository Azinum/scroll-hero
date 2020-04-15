// image.h

#ifndef _IMAGE_H
#define _IMAGE_H

#include <stdint.h>

struct Image {
  unsigned char* pixel_buffer;
  int width;
  int height;
  int depth;
  int pitch;
};

int image_load_png(const char* file_name, struct Image* image);

void image_free_pixel_buffer(unsigned char* pixel_buffer);

#endif