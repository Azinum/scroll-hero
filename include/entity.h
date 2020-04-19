// entity.h

#ifndef _ENTITY_H
#define _ENTITY_H

enum Entity_flags {
  FLAGS_COLLIDABLE  = 1 << 0,
  FLAGS_VISIBLE     = 1 << 1,
  FLAGS_STATIC      = 1 << 2,
};

struct Box {
  uint8_t top;
  uint8_t bottom;
  uint8_t left;
  uint8_t right;
};

struct Entity {
  struct Entity* prev;
  struct Entity* next;
  int16_t id;
  int32_t flags;
  int16_t type;
  int32_t x;
  int32_t y;
  int32_t x_next;
  int32_t y_next;
  int16_t x_speed;
  int16_t y_speed;
  uint8_t grounded;
  int16_t interval;
  struct Box hitbox;
};

extern struct Entity* entities;
extern struct Entity* inactive_entities;

struct Entity* entity_add(int32_t x, int32_t y, int16_t type);

struct Entity* entity_remove(struct Entity* entity);

void entities_update();

void entities_render();

void entities_clear();

#endif