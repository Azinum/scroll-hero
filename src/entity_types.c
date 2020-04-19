// entity_types.c

#include "common.h"
#include "entity_types.h"

struct Entity_type_def entity_types[] = {
  {ENTITY_PLAYER, NULL, NULL, NULL},
  {ENTITY_MONSTER, &init_monster, &update_monster, &destroy_monster},
};