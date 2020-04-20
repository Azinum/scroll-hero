// entity.c

#include "entity_common.h"
#include "render.h"

#include "entity.h"

int32_t entity_count = 0;
struct Entity* entities = NULL;
struct Entity* inactive_entities = NULL;

static struct Entity* entity_alloc();
static uint8_t entity_collision(struct Entity* e);

struct Entity* entity_alloc() {
  struct Entity* entity = malloc(sizeof(struct Entity));
  if (!entity) {
    log_printf("Failed to allocate memory for entity\n");
    return NULL;
  }
  memset(entity, 0, sizeof(struct Entity));
  return entity;
}

#define TEMP_WIDTH  32
#define TEMP_HEIGHT 32

// Minkowski sum to check collisions
uint8_t entity_collision(struct Entity* e) {
  struct Entity* target = entities;
  while (target) {
    struct Entity* next = target->next;

    if (e == target) {
      target = next;
      continue;
    }
    if (target->flags & FLAGS_COLLIDABLE) {
      // Temporarily having hardcoded width and height here
      int32_t w = (TEMP_WIDTH + TEMP_WIDTH) >> 1; // target->w + e->w
      int32_t h = (TEMP_HEIGHT + TEMP_HEIGHT) >> 1; // target->w + e->w
      int32_t dx = (e->x_next + (TEMP_WIDTH >> 1)) - (target->x + (TEMP_WIDTH >> 1));
      int32_t dy = (e->y_next + (TEMP_HEIGHT >> 1)) - (target->y + (TEMP_HEIGHT >> 1));
      if (abs(dx) <= w && abs(dy) <= h) {
        int32_t wy = w * dy;
        int32_t hx = h * dx;

        if (wy > hx) {
          if (wy > -hx) { // Top
            e->y_next -= (dy - h);
            e->y_speed = 0;
          }
          else {   // Right
            e->x_next -= (dx + w);
            e->x_speed = 0;
          }
        }
        else {
          if (wy > -hx) {   // Left
            e->x_next -= (dx - w);
            e->x_speed = 0;
          }
          else {   // Bottom
            e->y_next -= (dy + h);
            e->y_speed = 0;
            e->grounded = 1;
          }
        }
      }
    }
    target = next;
  }
  return 0;
}

struct Entity* entity_add(int32_t x, int32_t y, int16_t type) {
  short id = entity_count++;
  struct Entity* e = entity_alloc();
  if (!e)
    return NULL;
  e->id = id;
  e->x = e->x_next = x;
  e->y = e->y_next = y;
  e->flags = FLAGS_VISIBLE;
  e->type = type;
  if (e->type > 0) {
    entity_types[e->type].init(e);
  }
  LIST_PUSH(entities, e);
  return e;
}

struct Entity* entity_delete(struct Entity* entity) {
  struct Entity* next = entity->next;
  LIST_REMOVE(entities, entity);
  free(entity);
  entity_count--;
  return next;
}

void entities_update() {
  struct Entity* entity = entities;
  struct Entity* next;
  while (entity) {
    next = entity->next;
    if (entity->type > 0) {
      entity_types[entity->type].update(entity);
    }
    if (entity->flags & FLAGS_STATIC) {
      entity = next;
      continue;
    }

    if (entity->flags & FLAGS_COLLIDABLE) {
      entity->x_next += entity->x_speed;
      entity->y_next += entity->y_speed;
      entity->grounded = 0;
      entity_collision(entity);
      entity->x = entity->x_next;
      entity->y = entity->y_next;
    }
    entity = next;
  }
}

void entities_render() {
  const struct Entity* e = entities;
  while (e) {
    if (e->flags & FLAGS_VISIBLE) {
      render_texture(e->x - camera.x, e->y - camera.y, 32, 32, e->flipped, NULL);
    }
    e = e->next;
  }
}

void entities_clear() {
  LIST_CLEAR(entities);
  LIST_CLEAR(inactive_entities);
  entity_count = 0;
}