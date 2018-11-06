#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "events.h"
#include "tick.h"
#include "render.h"
#include "states.h"


void menuEvents() {
  SDL_Event e;
  
  while(SDL_PollEvent(&e)) {
    if(e.type == SDL_QUIT) quit = true;
  }
}

void menuTick() {
  char str[12];
  sprintf(str, "%d", tickNo);
  write(1, 1, str, 0xFFF, 0x555);
}

void menuRedraw() {
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

    uint8_t r = (screen[i+1] & 0x0F)*17,
            g = (screen[i+2] >> 4)*17,
            b = (screen[i+2] & 0x0F)*17,
            rb = (screen[i+3] & 0x0F)*17,
            gb = (screen[i+4] >> 4)*17,
            bb = (screen[i+4] & 0x0F)*17;

    SDL_SetRenderDrawColor(renderer, rb, gb, bb, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &dst);
    SDL_SetTextureColorMod(tileset, r, g, b);
    SDL_RenderCopy(renderer, tileset, &src, &dst);
  }
  
  SDL_RenderPresent(renderer);
}

State menuState = {
  .events = menuEvents,
  .tick   = menuTick,
  .redraw = menuRedraw
};