#ifndef MOVE_H
#define MOVE_H
#include <SDL2/SDL.h>
#include "structs.h"
#include <stdbool.h>
void resetBall(Ball* ball);
void moveAIPaddle(SDL_Rect* paddle, Ball* ball);
void movePaddle(SDL_Event* e, SDL_Rect* paddle);
bool moveBall(Ball* ball, SDL_Rect* paddle1, SDL_Rect* paddle2);
#endif
