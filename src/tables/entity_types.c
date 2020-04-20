// entity_types.c

#include "common.h"
#include "entity.h"
#include "tables.h"
#include "entity_types_gen.h"

struct Entity_type_def entity_types[] = {
  {ENTITY_PLAYER, NULL, NULL, NULL},
  {ENTITY_MONSTER, &init_monster, &update_monster, &destroy_monster},
};