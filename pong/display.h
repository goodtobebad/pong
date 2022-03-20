#ifndef DISPLAY_H
#define DISPLAY_H
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "structs.h"
  bool initVideo();
  void killDisplay();
  void updateScreen();
  void drawPaddle(SDL_Rect* paddle);
  void showScore(int* firstPlayer_score, int* secondPlayer_score);
  void drawBall(Ball* ball);
#endif
