// image.c

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <png.h>

#include "image.h"

int image_load_png(const char* file_name, struct Image* image) {
  FILE* file = fopen(file_name, "rb");
  assert(file != NULL);
  if (!file)
    return -1;

  unsigned char signature[8];
  if (fread(signature, 1, sizeof(signature), file) < 8) {
    fclose(file);
    return -1;
  }
  if (png_sig_cmp(signature, 0, 8)) {
    fclose(file);
    return -1;
  }
  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) {
    fclose(file);
    return -1;
  }
  png_infop info = png_create_info_struct(png);
  if (!info) {
    fclose(file);
    return -1;
  }
  if (setjmp(png_jmpbuf(png))) {
    png_destroy_read_struct(&png, &info, NULL);
    fclose(file);
    
    if (image->pixel_buffer != NULL) {
      free(image->pixel_buffer);
      image->pixel_buffer = NULL;
    }

    return -1;
  }
  png_init_io(png, file);
  png_set_sig_bytes(png, sizeof(signature));
  png_read_info(png, info);

  image->width = png_get_image_width(png, info);
  image->height = png_get_image_height(png, info);
  image->depth = png_get_bit_depth(png, info);

  if (image->depth < 8)
    png_set_packing(png);

  if (png_get_valid(png, info, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png);

  switch (png_get_color_type(png, info)) {
    case PNG_COLOR_TYPE_GRAY: {
      image->pitch = 3 * image->width;
      png_set_gray_to_rgb(png);
      break;
    }

    case PNG_COLOR_TYPE_GRAY_ALPHA: {
      image->pitch = 4 * image->width;
      png_set_gray_to_rgb(png);
      break;
    }

    case PNG_COLOR_TYPE_PALETTE: {
      image->pitch = 3 * image->width;
      png_set_expand(png);
      break;
    }

    case PNG_COLOR_TYPE_RGB: {
      image->pitch = 3 * image->width;
      break;
    }

    case PNG_COLOR_TYPE_RGBA: {
      image->pitch = 4 * image->width;
      break;
    }

    default:
      assert(0);
      return -1;
  }

  unsigned int bpp = png_get_rowbytes(png, info) / image->width;

  png_set_interlace_handling(png);
  png_read_update_info(png, info);

  image->pixel_buffer = malloc(sizeof(unsigned char) * image->width * image->height * bpp);
  png_bytep rows[image->height];

  unsigned char* pixels = image->pixel_buffer;
  for (int i = 0; i < image->height; i++) {
    rows[i] = pixels;
    pixels += image->width * bpp;
  }

  png_read_image(png, rows);
  png_read_end(png, NULL);
  png_destroy_read_struct(&png, &info, NULL);

  fclose(file);
  return 0;
}


void image_free_pixel_buffer(unsigned char* pixel_buffer) {
  assert(pixel_buffer != NULL);
  free(pixel_buffer);
}