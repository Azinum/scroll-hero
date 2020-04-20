// table.h

#ifndef _TABLES_H
#define _TABLES_H

struct Entity;

enum Entity_type {
  ENTITY_PLAYER,
  ENTITY_MONSTER,
};

typedef void (*entity_func)(struct Entity*);

struct Entity_type_def {
  int16_t type;
  entity_func init;
  entity_func update;
  entity_func destroy;
};

extern struct Entity_type_def entity_types[];

#endif