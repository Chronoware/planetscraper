#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "events.h"
#include "tick.h"
#include "render.h"
#include "states.h"
#include "stateMenu.h"


void introEvents() {
  SDL_Event e;
  
  while(SDL_PollEvent(&e)) {
    if(e.type == SDL_QUIT) quit = true;
  }
}

void introTick() {
  if(tickNo == 0) {
    write(SCREEN_W/2 - 5, SCREEN_H/2 + 5, "Chronoware", 0x0F0, 0);
    write(SCREEN_W/2 - 2, SCREEN_H/2 + 6,    "Games"  , 0xFFF, 0);
  }
  if(tickNo == 50) nextState = &menuState;
}

void introRedraw() {
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
            b = (screen[i+2] & 0x0F)*17;
  
    SDL_SetTextureColorMod(tileset, r, g, b);
    SDL_RenderCopy(renderer, tileset, &src, &dst);
  }
  
  SDL_RenderPresent(renderer);
}

State introState = {
  .events = introEvents,
  .tick   = introTick,
  .redraw = introRedraw
};