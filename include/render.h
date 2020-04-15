// render.h

#ifndef _RENDER_H
#define _RENDER_H

void render_rect(int x, int y, int w, int h, int r, int g, int b, int a);

void render_fill_rect(int x, int y, int w, int h, int r, int g, int b, int a);

void render_text(int x, int y, float size, const char* text);

void render_texture(int x, int y, int w, int h, void* texture);

#endif