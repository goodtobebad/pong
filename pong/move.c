#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "structs.h"

#define SCREEN_W 600
#define SCREEN_H 400

#define PADDLE_W (SCREEN_W / 25)
#define PADDLE_H (SCREEN_H / 3)

void resetBall(Ball* ball) {
  ball -> radius = 9;
  ball -> y = SCREEN_H / 2;
  ball -> x = SCREEN_W / 2;
  ball -> dx = 3;
  do {
    ball -> dy = (rand() % 6) - 3;
  } while(ball -> dy == 0);
}

void moveFirstPlayerPaddle(SDL_Event* e, SDL_Rect* paddle) {
  int move_unit = 8;
  if(e -> type == SDL_KEYDOWN) {
    switch(e -> key.keysym.sym) {
      case SDLK_z:
        if(paddle -> y >= 0) {
          paddle -> y -= move_unit;
        }
        break;
      case SDLK_s:
        if(paddle -> y <= SCREEN_H - PADDLE_H) {
          paddle -> y += move_unit;
        }
        break;
    }
  }
}

void moveSecondPlayerPaddle(SDL_Event* e, SDL_Rect* paddle) {
  int move_unit = 8;
  if(e -> type == SDL_KEYDOWN) {
    switch(e -> key.keysym.sym) {
      case SDLK_UP:
        if(paddle -> y >= 0) {
          paddle -> y -= move_unit;
        }
        break;
      case SDLK_DOWN:
        if(paddle -> y <= SCREEN_H - PADDLE_H) {
          paddle -> y += move_unit;
        }
        break;
    }
  }
}

bool moveBall(Ball* ball, SDL_Rect* paddle1, SDL_Rect* paddle2, bool playerOne_scored, bool playerTwo_scored) {
  playerOne_scored = false;
  playerTwo_scored = false;
  
  //Right Paddle Hit
  if(ball -> x <= (paddle1 -> x) + PADDLE_W + 3
      && ball -> x >= paddle1 -> x
      && ball -> y <= paddle1 -> y + PADDLE_H 
      && ball -> y >= paddle1 -> y) {

      ball -> dx = - ball -> dx;
  }

  if(ball -> y <= (paddle1 -> y) + PADDLE_H + 3
      && ball -> y >= paddle1 -> y
      && ball -> x <= paddle1 -> x + PADDLE_W) {

    ball -> dy = - ball -> dy;
  }

  if(ball -> y >= SCREEN_H || ball -> y < 0) {
    ball -> dy = - ball -> dy;
  }

  //Left Paddle Hit
  if(ball -> x <= paddle2 -> x + PADDLE_W + 3
      && ball -> x >= paddle2 -> x
      && ball -> y <= paddle2 -> y + PADDLE_H 
      && ball -> y >= paddle2 -> y) {

    ball -> dx = - ball -> dx;
  }

  ball -> x += ball -> dx;
  ball -> y += ball -> dy;

  if(ball -> x <= 0 || ball -> x >= SCREEN_W) {

    if(ball -> x <= 0) {
      playerOne_scored = true;
    }else {
      playerTwo_scored = true;
    }

    return true;
  }
  else {
    return false;
  }
}
