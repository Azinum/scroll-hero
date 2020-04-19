// monster.c

#include "common.h"
#include "game.h"
#include "entity.h"
#include "entity_types.h"

static int16_t gravity = 1;

void init_monster(struct Entity* entity) {
  entity->flags |= FLAGS_COLLIDABLE;
  entity->interval = 25 + (5 * entity->id);
}

void update_monster(struct Entity* entity) {
  if (!(game_tick % 5))
    entity->y_speed += gravity;

  if (!(game_tick % entity->interval)) {
    if (entity->grounded)
      entity->y_speed = -5;
  }
}

void destroy_monster(struct Entity* entity) {

}
