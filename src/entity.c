// entity.c

#include <string.h>
#include <math.h>

#include "common.h"
#include "camera.h"
#include "list.h"
#include "render.h"
#include "game.h"
#include "entity.h"

static int32_t entity_count = 0;
struct Entity* entities = NULL;
struct Entity* inactive_entities = NULL;

static struct Entity* entity_alloc();
static uint8_t entity_collision(struct Entity* e);

struct Entity* entity_alloc() {
  struct Entity* entity = malloc(sizeof(struct Entity));
  if (!entity) {
    log_out("Failed to allocate memory for entity\n");
    return NULL;
  }
  memset(entity, 0, sizeof(struct Entity));
  return entity;
}

#define TEMP_WIDTH  32
#define TEMP_HEIGHT 32

// Minkowski sum to check collisions
uint8_t entity_collision(struct Entity* e) {
  struct Entity* entity = entities;
  while (entity) {
    struct Entity* next = entity->next;

    if (e == entity) {
      entity = next;
      continue;
    }
    if (entity->flags & ENTITY_STATIC) {
      // Temporarily having hardcoded width and height here
      int32_t w = (TEMP_WIDTH + TEMP_WIDTH) >> 1; // target->w + e->w
      int32_t h = (TEMP_HEIGHT + TEMP_HEIGHT) >> 1; // target->w + e->w
      int32_t dx = (e->x_next + (TEMP_WIDTH >> 1)) - (entity->x + (TEMP_WIDTH >> 1));
      int32_t dy = (e->y_next + (TEMP_HEIGHT >> 1)) - (entity->y + (TEMP_HEIGHT >> 1));
      if (abs(dx) <= w && abs(dy) <= h) {
        int32_t wy = w * dy;
        int32_t hx = h * dx;

        if (wy > hx) {
          if (wy > -hx) { // Top
            e->y_next = entity->y + TEMP_HEIGHT; // + target->body.h
            e->y_speed = 0;
          }
          else {   // Right
            e->x_next = entity->x - TEMP_WIDTH; // - entity->body.w;
            e->x_speed = 0;
          }
        }
        else {
          if (wy > -hx) {   // Left
            e->x_next = entity->x + TEMP_WIDTH; // + target->body.w;
            e->x_speed = 0;
          }
          else {   // Bottom
            e->y_next = entity->y - TEMP_HEIGHT; // - entity->body.h;
            e->y_speed = 0;
            e->grounded = 1;
          }
        }
      }
    }

    entity = next;
  }
  return 0;
}

struct Entity* entity_add(int32_t x, int32_t y) {
  short id = entity_count++;
  struct Entity* e = entity_alloc();
  if (!e)
    return NULL;
  e->id = id;
  e->x = e->x_next = x;
  e->y = e->y_next = y;
  e->flags = ENTITY_STATIC | ENTITY_VISIBLE;
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
    if (entity->flags & ENTITY_MOVABLE) {
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
    if (e->flags & ENTITY_VISIBLE) {
      render_texture(e->x - camera.x, e->y - camera.y, 32, 32, NULL);
      render_rect(e->x - camera.x, e->y - camera.y, 32, 32, 100, 100, 255, 255);
    }
    e = e->next;
  }
}

void entities_clear() {
  LIST_CLEAR(entities);
  LIST_CLEAR(inactive_entities);
}