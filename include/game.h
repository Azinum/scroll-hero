// game.h

#ifndef _GAME_H
#define _GAME_H

extern double deltatime;
extern double totaltime;
extern int16_t game_tick;

int game_execute(int argc, char** argv);

#endif