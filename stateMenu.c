#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "events.h"
#include "tick.h"
#include "render.h"
#include "states.h"
#include "colors.h"

#define OPTIONS 5
#define SETTINGS 1

static int currentScreen = 0;
static int currentOptions = OPTIONS;
static int choice = 0;
static char options[OPTIONS][16] = {
  "New game",
  "Load game",
  "Settings",
  "Credits",
  "Exit"
};
static char settings[SETTINGS][32] = {
  "Show current tick"
};
static bool settingVals[SETTINGS] = {
  false //showTick
};

void menuEvents() {
  SDL_Event e;
  
  while(SDL_PollEvent(&e)) {
    switch(e.type) {
      case SDL_QUIT:
        quit = true;
        break;
      
      case SDL_KEYDOWN:
        switch(e.key.keysym.sym) {
          case SDLK_UP:
            if(--choice == -1) choice = currentOptions - 1;
            break;

          case SDLK_DOWN:
            if(++choice == currentOptions) choice = 0;
            break;

          case SDLK_RETURN:
            clearScreen();
            if(currentScreen == 0){
              if(!strcmp(options[choice], "Exit")) quit = true;
              if(!strcmp(options[choice], "Settings")) {
                currentOptions = SETTINGS + 1;
                currentScreen = 3;
                choice = 0;
                break;
              }
            }
            if(currentScreen == 3){
              if(choice == SETTINGS){
                currentOptions = OPTIONS;
                currentScreen = 0;
                choice = 0;
                break;
              } else{
                settingVals[choice] = !settingVals[choice];
              }
            }
            break;
        }
        break;
    }
  }
}

void menuTick() {
  if(tickNo == 0) clearScreen();
  //if(settingVals[0])write(2, 1, tickNo, COLOR_WHITE, COLOR_GRAY);

  if(currentScreen == 0){
    for(int i=0; i<OPTIONS; i++) {
      write(1, SCREEN_H/2 + 5 + i + (i==OPTIONS-1 ? 1 : 0), options[i], choice == i ? COLOR_GREEN : COLOR_WHITE, 0);
    }
  }
  if(currentScreen == 3){
    for(int i=0; i<SETTINGS; i++) {
      write(1, SCREEN_H/2 + 5 + i + (i==SETTINGS-1 ? 1 : 0), settings[i], choice == i ? COLOR_GREEN : COLOR_WHITE, 0);
      write(SCREEN_W-4, SCREEN_H/2 + 5 + i + (i==SETTINGS-1 ? 1 : 0), settingVals[i] ? "ON" : "OFF", settingVals[i] ? COLOR_BLACK : COLOR_WHITE, settingVals[i] ? COLOR_GREEN : COLOR_RED);
    }
    write(1, SCREEN_H/2 + 5 + SETTINGS+2, "Return", choice == SETTINGS ? COLOR_GREEN : COLOR_WHITE, 0);
  }
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