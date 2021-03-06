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

#define BAR_W (SCREEN_W / 25)
#define BAR_H (SCREEN_H / 3)

int main() {
  const int gameTick = 128;
  const int waitTime = 1000.0f/gameTick;
  int next_game_step = SDL_GetTicks();
  int playerOne_scored = 0;
  int playerTwo_scored = 0;
  int score_playerOne = 0;
  int score_playerTwo = 0;
 
  const int renderFPS = 1000.0f/60;
  int frameStartTime = 0;

  //Create Game Objects
  SDL_Rect bar1 = {10, (SCREEN_H / 2) - (BAR_H / 2), BAR_W, BAR_H}; 
 
  SDL_Rect bar2 = {SCREEN_W - BAR_W - 10, (SCREEN_H / 2) - (BAR_H / 2), BAR_W, BAR_H};

  srand(time(0));
  Ball ball;
  resetBall(&ball);

  initVideo();
  bool quit = false;
  bool paused = true;
  bool ball_out = false;

  SDL_Event e;
  drawBar(&bar2);
  drawBar(&bar1);
  drawBall(&ball);
  updateScreen();

  while(!quit) {
    int now = SDL_GetTicks();

    if(next_game_step <= now) {
      int limit = 10;
      while((next_game_step <= now) && (limit--)) {
        if(!paused) {
          ball_out = moveBall(&ball, &bar1, &bar2, &playerOne_scored, &playerTwo_scored);
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
              moveFirstPlayerBar(&e, &bar1);
              moveSecondPlayerBar(&e, &bar2);
            }
          }
        }
        next_game_step += waitTime;
      }

      if(!paused) {
        drawBar(&bar2);
        drawBar(&bar1);
        drawBall(&ball);
        updateScreen();
      }
    }

    int delayTime = renderFPS - (SDL_GetTicks() - frameStartTime);
    if(delayTime > 0) {
      SDL_Delay(delayTime);
    }
    frameStartTime = SDL_GetTicks();

    if(ball_out) {
      paused = true;

      if(playerOne_scored == 1) {
        score_playerOne += 1;
      }

      if(playerTwo_scored == 1) {
        score_playerTwo += 1;
      }

      if(score_playerOne >= 3) {
        SDL_Delay(1000);

        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Win", "Player one wins", NULL);

        killDisplay();
      }

      if(score_playerTwo >= 3) {
        SDL_Delay(1000);

        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Win", "Player two wins", NULL);

        killDisplay();
      }

      playerOne_scored = 0;
      playerTwo_scored = 0;

      resetBall(&ball);
    }

  }
  killDisplay();
  return 0;
}
