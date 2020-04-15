// render.h

#ifndef _RENDER_H
#define _RENDER_H

void render_rect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, int32_t g, int32_t b, int32_t a);

void render_fill_rect(int32_t x, int32_t y, int32_t w, int32_t h, int32_t r, int32_t g, int32_t b, int32_t a);

void render_text(int32_t x, int32_t y, float size, const char* text);

void render_texture(int32_t x, int32_t y, int32_t w, int32_t h, void* texture);

#endif