// window.h

#ifndef _WINDOW_H
#define _WINDOW_H

int window_init(const char* screen_title, int screen_width, int screen_height);

void* window_renderer();

const unsigned char* window_keyboardstate();

int window_pollevent();

void window_change_title(const char* new_title);

void window_clear();

void window_render();

void window_free();

#endif