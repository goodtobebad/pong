#include <SDL2/SDL.h>
#include <stdbool.h>
#include "structs.h"

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 400;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

void updateScreen() {
  SDL_RenderPresent(gRenderer);

  SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
  SDL_RenderClear( gRenderer );
}

bool initVideo() {
  bool success = true;
  if(SDL_Init(SDL_INIT_VIDEO) < 0) { success = false; }
  else {
    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Linear filtering not enabled!");
    }

    gWindow = SDL_CreateWindow("Pong",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    
    if(gWindow == NULL) {
      success = false;
    }
    else {
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
      if(gRenderer == NULL) {
        success = false;
      }
      else {
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
      }
    }
  }
  return success;
}

void killDisplay() {
  SDL_DestroyRenderer(gRenderer);
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  gRenderer = NULL;

  SDL_Quit();
}

void drawBar(SDL_Rect* bar) {
  SDL_SetRenderDrawColor(gRenderer, 102, 255, 102, 0xFF);
  SDL_RenderFillRect(gRenderer, bar);
}

void drawBall(Ball* ball) {
  int x0 = ball -> x;
  int y0 = ball -> y;
  int r = ball -> radius;
  
  SDL_SetRenderDrawColor(gRenderer, 102, 255, 102, 0xFF);
  int x = r - 1;
  int y = 0;
  int dx = 1;
  int dy = 1;
  int err = dx - (r << 1);

  while(x >= y) {
    SDL_RenderDrawPoint(gRenderer, x0 + x, y0 + y);
    SDL_RenderDrawPoint(gRenderer, x0 + y, y0 + x);
    SDL_RenderDrawPoint(gRenderer, x0 - y, y0 + x);
    SDL_RenderDrawPoint(gRenderer, x0 - x, y0 + y);
    SDL_RenderDrawPoint(gRenderer, x0 - x, y0 - y);
    SDL_RenderDrawPoint(gRenderer, x0 - y, y0 - x);
    SDL_RenderDrawPoint(gRenderer, x0 + y, y0 - x);
    SDL_RenderDrawPoint(gRenderer, x0 + x, y0 - y);

    if(err <= 0) {
      y++;
      err += dy;
      dy += 2;
    }
    if(err > 0) {
      x--;
      dx += 2;
      err += dx - (r << 1);
    }
  }
}
