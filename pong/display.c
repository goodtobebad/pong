#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
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

void drawPaddle(SDL_Rect* paddle) {
  SDL_SetRenderDrawColor(gRenderer, 102, 255, 102, 0xFF);
  SDL_RenderFillRect(gRenderer, paddle);
}

void showScore(int* firstPlayer_score, int* secondPlayer_score) {
  TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 24);
  SDL_Color White = {255, 255, 255};
  SDL_Surface* surfaceMessage =
    TTF_RenderText_Solid(Sans, "0 | 0", White);

  SDL_SetRenderDrawColor(gRenderer, 102, 255, 102, 0xFF);
  SDL_Texture* Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage);

  SDL_Rect Message_rect;
  Message_rect.x = SCREEN_WIDTH / 2;
  Message_rect.y = SCREEN_HEIGHT;
  Message_rect.w = SCREEN_WIDTH / 3;
  Message_rect.h = SCREEN_HEIGHT / 25;

  SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect);

  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(Message);
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
