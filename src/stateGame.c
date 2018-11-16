#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "events.h"
#include "tick.h"
#include "render.h"
#include "states.h"
#include "colors.h"
#include "stateMenu.h"
#include "stateGame.h"

void gameEvents() {
  SDL_Event e;
  
  while(SDL_PollEvent(&e)) {
    switch(e.type) {
      case SDL_QUIT:
        quit = true;
        break;
      
      case SDL_KEYDOWN:
        switch(e.key.keysym.sym) {
          case SDLK_ESCAPE:
            nextState = &menuState;
            break;
        }
        break;
    }
  }
}

void gameTick() {
  clearScreen();

  char s[20];
  sprintf(s, "Game, tick: %d", tickNo);
  write(1, 1, s, COLOR_GREEN, COLOR_BLACK);
}

void gameRedraw() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  for(uint32_t i=0; i<SCREEN_W * SCREEN_H * 5; i += 5) {
    if(screen[i] == 0) continue;

    SDL_Rect src;
    src.x = (screen[i]%16)*tileW; src.w = tileW;
    src.y = (screen[i]/16)*tileH; src.h = tileH;

    SDL_Rect dst;
    dst.x = ((i/5)%SCREEN_W)*tileW*zoom; dst.w = tileW*zoom;
    dst.y = ((i/5)/SCREEN_W)*tileH*zoom; dst.h = tileH*zoom;

    uint8_t r = fgRed(screen, i),
            g = fgGreen(screen, i),
            b = fgBlue(screen, i),
            rb = bgRed(screen, i),
            gb = bgGreen(screen, i),
            bb = bgBlue(screen, i);

    SDL_SetRenderDrawColor(renderer, rb, gb, bb, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &dst);
    SDL_SetTextureColorMod(tileset, r, g, b);
    SDL_RenderCopy(renderer, tileset, &src, &dst);
  }
  
  SDL_RenderPresent(renderer);
}


State gameState = {
  .events = gameEvents,
  .tick   = gameTick,
  .redraw = gameRedraw
};