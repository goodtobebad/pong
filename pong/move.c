#include <SDL2/SDL.h>
#include <stdbool.h>
#include "structs.h"

#define SCREEN_W 600
#define SCREEN_H 400

#define BAR_W (SCREEN_W / 25)
#define BAR_H (SCREEN_H / 3)

void resetBall(Ball* ball) {
  ball -> radius = 9;
  ball -> y = SCREEN_H / 2;
  ball -> x = SCREEN_W / 2;
  ball -> dx = 3;
  do {
    ball -> dy = (rand() % 6) - 3;
  } while(ball -> dy == 0);
}

void moveFirstPlayerBar(SDL_Event* e, SDL_Rect* bar) {
  int move_unit = 13;
  if(e -> type == SDL_KEYDOWN) {
    switch(e -> key.keysym.sym) {
      case SDLK_z:
        if(bar -> y >= 0) {
          bar -> y -= move_unit;
        }
        break;
      case SDLK_s:
        if(bar -> y <= SCREEN_H - BAR_H) {
          bar -> y += move_unit;
        }
        break;
    }
  }
}

void moveSecondPlayerBar(SDL_Event* e, SDL_Rect* bar) {
  int move_unit = 13;
  if(e -> type == SDL_KEYDOWN) {
    switch(e -> key.keysym.sym) {
      case SDLK_UP:
        if(bar -> y >= 0) {
          bar -> y -= move_unit;
        }
        break;
      case SDLK_DOWN:
        if(bar -> y <= SCREEN_H - BAR_H) {
          bar -> y += move_unit;
        }
        break;
    }
  }
}

bool moveBall(Ball* ball, SDL_Rect* bar1, SDL_Rect* bar2, int *playerOne_scored, int *playerTwo_scored) {
  if(ball -> x <= (bar1 -> x) + BAR_W + 3
      && ball -> x >= bar1 -> x
      && ball -> y <= bar1 -> y + BAR_H 
      && ball -> y >= bar1 -> y) {

      ball -> dx = - ball -> dx;
  }

  if(ball -> y <= (bar1 -> y) + BAR_H + 3
      && ball -> y >= bar1 -> y
      && ball -> x <= bar1 -> x + BAR_W) {

    ball -> dy = - ball -> dy;
  }

  if(ball -> y >= SCREEN_H || ball -> y < 0) {
    ball -> dy = - ball -> dy;
  }

  if(ball -> x <= bar2 -> x + BAR_W + 3
      && ball -> x >= bar2 -> x
      && ball -> y <= bar2 -> y + BAR_H 
      && ball -> y >= bar2 -> y) {

    ball -> dx = - ball -> dx;
  }

  ball -> x += ball -> dx;
  ball -> y += ball -> dy;

  if(ball -> x <= 0 || ball -> x >= SCREEN_W) {

    if(ball -> x <= 0) {
      *playerTwo_scored = 1;
    }else {
      *playerOne_scored = 1;
    }

    return true;
  }
  else {
    return false;
  }
}
