#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "events.h"
#include "tick.h"
#include "render.h"
#include "states.h"
#include "colors.h"
#include "stateNewgame.h"

#define OPTIONS 5
#define SETTINGS 1
#define CREDITS 4

static int currentCredit = 0;
static int currentScreen = 0;
static int choicesCount = OPTIONS;
static int choice = 0;
static char options[OPTIONS][16] = {
  "New game",
  "Load game",
  "Settings",
  "Credits",
  "Exit"
};
static char settings[SETTINGS][24] = {
  "Show current tick"
};
static char credits[CREDITS][32] = {
  "Code",
  "Voltinus",
  "Code",
  "Topkeksimus"
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
            if(--choice == -1) choice = choicesCount - 1;
            break;

          case SDLK_DOWN:
            if(++choice == choicesCount) choice = 0;
            break;

          case SDLK_RETURN:
            if(currentScreen == 0) {
              if(!strcmp(options[choice], "Exit")) quit = true; else
              if(!strcmp(options[choice], "New game")) nextState = &newgameState; else
              if(!strcmp(options[choice], "Settings")) {
                choicesCount = SETTINGS + 1;
                currentScreen = 3;
                choice = 0;
                break;
              }
              if(!strcmp(options[choice], "Credits")) {
                currentScreen = 4;
                currentCredit = 0;
                break;
              }
            }
            if(currentScreen == 3) {
              if(choice == SETTINGS) {
                choicesCount = OPTIONS;
                currentScreen = 0;
                choice = 0;
                break;
              } else {
                settingVals[choice] = !settingVals[choice];
              }
            }
            break;

            case SDLK_ESCAPE:
              if(currentScreen == 0){
                quit = true;
              }
              else{
                choicesCount = OPTIONS;
                currentScreen = 0;
                choice = 0;
              }
        }
        break;
    }
  }
}

void menuTick() {
  clearScreen();
  
  if(settingVals[0]) {
    char tickNoString[16];
    sprintf(tickNoString, "%d", tickNo);
    write(1, 1, tickNoString, COLOR_WHITE, COLOR_BLACK);
  }

  switch(currentScreen) {
    case 0: // main menu
      for(int i=0; i<OPTIONS; i++) {
        write(1, SCREEN_H/2 + 5 + i + (i==OPTIONS-1 ? 1 : 0), options[i], choice == i ? COLOR_GREEN : COLOR_WHITE, 0);
      }
      break;

    case 3: // options
      for(int i=0; i<SETTINGS; i++) {
        write(1, SCREEN_H/2 + 5 + i + (i==SETTINGS-1 ? 1 : 0), settings[i], choice == i ? COLOR_GREEN : COLOR_WHITE, 0);
        write(25, SCREEN_H/2 + 5 + i + (i==SETTINGS-1 ? 1 : 0), settingVals[i] ? "ON" : "OFF", settingVals[i] ? COLOR_BLACK : COLOR_WHITE, settingVals[i] ? COLOR_GREEN : COLOR_RED);
      }
      write(1, SCREEN_H/2 + 5 + SETTINGS+2, "Return", choice == SETTINGS ? COLOR_GREEN : COLOR_WHITE, 0);
      break;
    
    case 4: // credits
      if(tickNo%50 == 0) currentCredit++;
      if(currentCredit == CREDITS/2) currentCredit = 0;
      cwrite(SCREEN_W/2, SCREEN_H/2-1, credits[2*currentCredit], COLOR_BLACK, COLOR_GRAY);
      cwrite(SCREEN_W/2, SCREEN_H/2, credits[1+(2*currentCredit)], COLOR_GREEN, COLOR_BLACK);
      break;
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

State menuState = {
  .events = menuEvents,
  .tick   = menuTick,
  .redraw = menuRedraw
};