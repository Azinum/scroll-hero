// entity.h

#ifndef _ENTITY_H
#define _ENTITY_H

struct Entity {
  struct Entity* prev;
  struct Entity* next;
  short id;
  int x;
  int y;
  int w;
  int h;
};

extern struct Entity* entities;
extern struct Entity* inactive_entities;

struct Entity* entity_add(int x, int y);

struct Entity* entity_remove(struct Entity* entity);

void entities_update();

void entities_render();

void entities_clear();

#endif