// camera.h

#ifndef _CAMERA_H
#define _CAMERA_H

struct {
  int32_t x;
  int32_t y;
} camera;

void camera_init();

void camera_update();

#endif