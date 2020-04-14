// entity.h

#ifndef _ENTITY_H
#define _ENTITY_H

struct Entity {
  short id;
  int x;
  int y;
  int w;
  int h;
};

void entity_default(struct Entity* entity);

void entity_render(struct Entity* entity);

#endif