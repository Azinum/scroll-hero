// entity.c

#include <string.h>

#include "common.h"
#include "camera.h"
#include "list.h"
#include "render.h"
#include "entity.h"

static int32_t entity_count = 0;
struct Entity* entities = NULL;
struct Entity* inactive_entities = NULL;

static struct Entity* entity_alloc();

struct Entity* entity_alloc() {
  struct Entity* entity = malloc(sizeof(struct Entity));
  if (!entity) {
    log_out("Failed to allocate memory for entity\n");
    return NULL;
  }
  memset(entity, 0, sizeof(struct Entity));
  return entity;
}

struct Entity* entity_add(int32_t x, int32_t y) {
  short id = entity_count++;
  struct Entity* e = entity_alloc();
  if (!e)
    return NULL;
  e->id = id;
  e->x = x;
  e->y = y;
  e->x_next = e->x;
  e->y_next = e->y;
  e->type = ENTITY_MOVABLE | ENTITY_VISIBLE;
  LIST_PUSH(entities, e);
  return e;
}

struct Entity* entity_remove(struct Entity* entity) {
  struct Entity* next = entity->next;
  LIST_REMOVE(entities, entity);
  free(entity);
  return next;
}

void entities_update() {
  struct Entity* entity = entities;
  struct Entity* next;
  while (entity) {
    next = entity->next;
    if (entity->type & ENTITY_MOVABLE) {
      if (1) {  // If not colliding
        entity->x_next += entity->x_speed;
        entity->y_next += entity->y_speed;
      }
      // TODO: ^^^ Check collision, add amount of pixels moved
      // to x_next and y_next and apply them here:
      entity->x = entity->x_next;
      entity->y = entity->y_next;
    }
    entity = next;
  }
}

void entities_render() {
  const struct Entity* e = entities;
  while (e) {
    if (e->type & ENTITY_VISIBLE) {
      render_fill_rect(e->x - camera.x, e->y - camera.y, 32, 32, 110, 100, 255, 255);
    }
    e = e->next;
  }
}

void entities_clear() {
  LIST_CLEAR(entities);
  LIST_CLEAR(inactive_entities);
}