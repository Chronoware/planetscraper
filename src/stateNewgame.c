#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "events.h"
#include "tick.h"
#include "render.h"
#include "states.h"
#include "colors.h"
#include "stateMenu.h"
#include "stateNewgame.h"
#include "stateGame.h"

#define OPTIONS 4
#define SETTINGS 2

static int choice = 0;
static char options[OPTIONS][16] = {
  "World name:",
  "      Seed:",
  "Create world",
  "Back"
};
static char settings[SETTINGS][32] = {
  "Test", ""
};

uint32_t getSeed(char *s) {
  uint32_t seed = 0xABCDDCBA;

  for(int i=0; i<strlen(s); i++) {
    seed *= (s[i] + i);
  }

  return seed;
}

void newgameEvents() {
  SDL_Event e;
  
  while(SDL_PollEvent(&e)) {
    switch(e.type) {
      case SDL_QUIT:
        quit = true;
        break;
      
      case SDL_KEYDOWN:
        switch(e.key.keysym.sym) {
          case SDLK_UP:
            if(--choice == -1) choice = OPTIONS - 1;
            break;

          case SDLK_DOWN:
            if(++choice == OPTIONS) choice = 0;
            break;

          case SDLK_RETURN:
            if(!strcmp(options[choice], "Back")) nextState = &menuState;
            if(!strcmp(options[choice], "Create world") && strlen(settings[0])) {
              FILE *fp;
              char filename[38];
              char extension[7] = ".scrap";

              for(int i=0; i<strlen(settings[0]); i++) {
                filename[i] = settings[0][i];
              }

              for(int i=0; i<strlen(extension)+1; i++) {
                filename[i+strlen(settings[0])] = extension[i];
              }

              printf("%s\n", filename);

              if(!(fp = fopen(filename, "ab"))) { // file already exists
                fclose(fp);
                printf("File exists!\n");
                // @TODO: add warning
              } else {
                worldGen(fp);
                fclose(fp);
                nextState = &gameState;
              }
            }
            break;

          case SDLK_ESCAPE:
            nextState = &menuState;
            break;

          case SDLK_BACKSPACE:
            if(choice < SETTINGS && strlen(settings[choice])) {
              settings[choice][strlen(settings[choice])-1] = 0;
            }
            break;

          default:
            if(choice < SETTINGS && strlen(settings[choice]) < 31) {
              uint8_t pos = strlen(settings[choice]);
              settings[choice][pos]   = e.key.keysym.sym;
              settings[choice][pos+1] = 0;
            }
            break;
        }
        break;
    }
  }
}

void newgameTick() {
  clearScreen();

  for(int i=0; i<OPTIONS; i++) {
    write(1, SCREEN_H/2 + 5 + i + (i>OPTIONS-3 ? 1 : 0), options[i], choice == i ? COLOR_GREEN : COLOR_WHITE, 0);
  }

  for(int i=0; i<SETTINGS; i++) {
    write(13, SCREEN_H/2 + 5 + i, settings[i], choice == i ? COLOR_GREEN : COLOR_WHITE, 0);
  }
}

void newgameRedraw() {
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

void worldGen(FILE *fp) {
  char *signature = "SCRP";
  char *version   = "0001";
  char *worldName = malloc(33*sizeof(char));
  uint32_t seed = getSeed(settings[1]);

  for(uint8_t i=0; i<32; i++) {
    if(i < strlen(settings[0])) worldName[i] = settings[0][i];
    else worldName[i] = 0x20; // space character
  }
  worldName[32] = 0;

  fprintf(fp, signature);
  fprintf(fp, version);
  fprintf(fp, worldName);
  fprintf(fp, "%08X", seed);
  for(uint8_t i=0; i<16; i++) putc('0', fp);
}


State newgameState = {
  .events = newgameEvents,
  .tick   = newgameTick,
  .redraw = newgameRedraw
};