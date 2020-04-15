// player.h

#ifndef _PLAYER_H
#define _PLAYER_H

#include "entity.h"

extern struct Entity* player;

void player_init();

void player_update();

void player_render();

void player_free();

#endif