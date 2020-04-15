// image.h

#ifndef _IMAGE_H
#define _IMAGE_H

struct Image {
  uint8_t* pixel_buffer;
  int32_t width;
  int32_t height;
  int32_t depth;
  int32_t pitch;
};

int32_t image_load_png(const char* file_name, struct Image* image);

void image_free_pixel_buffer(uint8_t* pixel_buffer);

#endif