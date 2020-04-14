// entity.c

#include "common.h"
#include "camera.h"
#include "list.h"
#include "render.h"
#include "entity.h"

static int entity_count = 0;
struct Entity* entities = NULL;
struct Entity* inactive_entities = NULL;

static struct Entity* entity_alloc(int x, int y, int w, int h, short id);

struct Entity* entity_alloc(int x, int y, int w, int h, short id) {
  struct Entity* e = malloc(sizeof(struct Entity));
  if (!e)
    return NULL;
  e->id = id;
  e->x = x;
  e->y = y;
  e->w = w;
  e->h = h;
  return e;
}

struct Entity* entity_add(int x, int y) {
  short id = entity_count++;
  struct Entity* entity = entity_alloc(x, y, 20, 20, id);
  if (!entity) {
    log_out("Failed to allocate memory for entity\n");
    return NULL;
  }
  LIST_PUSH(entities, entity);
  return entity;
}

struct Entity* entity_remove(struct Entity* entity) {
  struct Entity* next = entity->next;
  LIST_REMOVE(entities, entity);
  free(entity);
  return next;
}

void entities_update() {
  struct Entity* e = entities;
  struct Entity* next;
  while (e) {
    next = e->next;
    e = next;
  }
}

void entities_render() {
  const struct Entity* e = entities;
  while (e) {
    render_fill_rect(e->x - camera.x, e->y - camera.y, e->w, e->h, 255, 100, 100, 255);
    e = e->next;
  }
}

void entities_clear() {
  LIST_CLEAR(entities);
  LIST_CLEAR(inactive_entities);
}