// window.h

#ifndef _WINDOW_H
#define _WINDOW_H

int window_init(const char* screen_title, int32_t screen_width, int32_t screen_height);

void* window_renderer();

void* window_font();

const uint8_t* window_keyboardstate();

int window_pollevent();

double window_time();

void window_change_title(const char* new_title);

void window_clear();

void window_render();

void window_free();

#endif