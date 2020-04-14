// entity.c

#include "render.h"
#include "entity.h"

static int entity_count = 0;

void entity_default(struct Entity* e) {
  e->id = entity_count++;
  e->x = 0;
  e->y = 0;
  e->w = 0;
  e->h = 0;
}

void entity_render(struct Entity* e) {
  render_rect(e->x, e->y, e->w, e->h, 255, 100, 100, 255);
}