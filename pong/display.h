#ifndef DISPLAY_H
#define DISPLAY_H
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "structs.h"
  bool initVideo();
  void killDisplay();
  void updateScreen();
  void drawBar(SDL_Rect* bar);
  void drawBall(Ball* ball);
#endif
