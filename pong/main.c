#include "display.h"
#include "structs.h"
#include "move.h"
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_W 600
#define SCREEN_H 400

#define PADDLE_W (SCREEN_W / 25)
#define PADDLE_H (SCREEN_H / 3)

int main() {
  const int gameTick = 128;
  const int waittime = 1000.0f/gameTick;
  int next_game_step = SDL_GetTicks(); //initial value
  int playerOne_scored = 0;
  int playerTwo_scored = 0;
  int score_playerOne = 0;
  int score_playerTwo = 0;
 
  const int renderFPS = 1000.0f/60;
  int framestarttime = 0;

  //Create Game Objects
  SDL_Rect paddle1 = {10, (SCREEN_H / 2) - (PADDLE_H / 2), PADDLE_W, PADDLE_H}; 
 
  SDL_Rect paddle2 = {SCREEN_W - PADDLE_W - 10, (SCREEN_H / 2) - (PADDLE_H / 2), PADDLE_W, PADDLE_H};

  srand(time(0));
  Ball ball;
  resetBall(&ball);

  initVideo();
  bool quit = false;
  bool paused = true;
  bool out_of_bounds = false;

  SDL_Event e;
  drawPaddle(&paddle2);
  drawPaddle(&paddle1);
  drawBall(&ball);
  updateScreen();
  //Game Loop
  while(!quit) {
    int now = SDL_GetTicks();
    //Game logic
    if(next_game_step <= now) {
      int limit = 10;
      while((next_game_step <= now) && (limit--)) {
        if(!paused) {
          out_of_bounds = moveBall(&ball, &paddle1, &paddle2, &playerOne_scored, &playerTwo_scored);
        }
        while(SDL_PollEvent(&e) != 0) {
          if(e.type == SDL_QUIT) {
            quit = true;
          }
          else if(e.type == SDL_KEYDOWN) {
            if(e.key.keysym.sym == SDLK_ESCAPE) {
              paused = !paused;
            }
            else if(!paused) {
              moveFirstPlayerPaddle(&e, &paddle1);
              moveSecondPlayerPaddle(&e, &paddle2);
            }
          }
        }
        next_game_step += waittime;
      }
      if(!paused) {
        //Rendering
        drawPaddle(&paddle2);
        drawPaddle(&paddle1);
        drawBall(&ball);
        updateScreen();
      }
    }
    //limit fps
    int delaytime = renderFPS - (SDL_GetTicks() - framestarttime);
    if(delaytime > 0) {
      SDL_Delay(delaytime);
    }
    framestarttime = SDL_GetTicks();

    if(out_of_bounds) {
      paused = true;

      if(playerOne_scored == 1) {
        score_playerOne += 1;
      }

      if(playerTwo_scored == 1) {
        score_playerTwo += 1;
      }

      if(score_playerOne >= 3) {
        SDL_Delay(1000);

        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
        "Win",
        "Player one wins",
        NULL);
      }

      if(score_playerTwo >= 3) {
        SDL_Delay(1000);

        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
        "Win",
        "Player two wins",
        NULL);
      }

      playerOne_scored = 0;
      playerTwo_scored = 0;

      resetBall(&ball);
    }

  }
  killDisplay();
  return 0;
}
