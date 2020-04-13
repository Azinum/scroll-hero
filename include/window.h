// window.h

#ifndef _WINDOW_H
#define _WINDOW_H

int window_init(const char* screen_title, int screen_width, int screen_height);

int window_pollevent();

void window_clear();

void window_render();

void window_free();

#endif