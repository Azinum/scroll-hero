// monster.c

#include "common.h"
#include "game.h"
#include "player.h"
#include "entity.h"
#include "entity_types.h"

const int16_t gravity = 1;
const int16_t speed = 2;
const int16_t view_distance = 200;

inline int32_t x_delta_from_player(struct Entity* entity) {
  return entity->x - player->x;
}

inline int32_t y_delta_from_player(struct Entity* entity) {
  return entity->y - player->y;
}

void init_monster(struct Entity* entity) {
  entity->flags |= FLAGS_COLLIDABLE;
  entity->interval = 25 + (5 * entity->id);
}

void update_monster(struct Entity* entity) {
  if (!(game_tick % 2))
    entity->y_speed += gravity;

  if (!(game_tick % entity->interval)) {
    if (entity->grounded)
      entity->y_speed = -5;
  }

  int32_t x_delta = x_delta_from_player(entity);
  int32_t y_delta = y_delta_from_player(entity);
  if ((y_delta > 0 && y_delta < view_distance) || (y_delta < 0 && y_delta > -view_distance)) {
    if (x_delta > 0 && x_delta < view_distance) {
      entity->x_speed = -speed;
    }
    else if (x_delta < 0 && x_delta > -view_distance) {
      entity->x_speed = speed;
    }
    else {
      entity->x_speed = 0;
    }
  }
}

void destroy_monster(struct Entity* entity) {

}
