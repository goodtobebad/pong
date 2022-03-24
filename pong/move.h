#ifndef MOVE_H
#define MOVE_H
#include <SDL2/SDL.h>
#include "structs.h"
#include <stdbool.h>
void resetBall(Ball* ball);
void moveFirstPlayerBar(SDL_Event* e, SDL_Rect* bar);
void moveSecondPlayerBar(SDL_Event* e, SDL_Rect* bar);
bool moveBall(Ball* ball, SDL_Rect* bar1, SDL_Rect* bar2, int *playerOne_scored, int *playerTwo_scored);
#endif
