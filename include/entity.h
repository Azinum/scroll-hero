// entity.h

#ifndef _ENTITY_H
#define _ENTITY_H

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
  int32_t x;
  int32_t y;
  int32_t x_next;
  int32_t y_next;
  struct Box hitbox;
};

extern struct Entity* entities;
extern struct Entity* inactive_entities;

struct Entity* entity_add(int32_t x, int32_t y);

struct Entity* entity_remove(struct Entity* entity);

void entities_update();

void entities_render();

void entities_clear();

#endif