#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "states.h"
#include "stateIntro.h"
#include "events.h"
#include "tick.h"
#include "render.h"

int main(int argc, char** argv) {
  if(!init()) {
    printf("0 SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  write(SCREEN_W/2 - 5, SCREEN_H/2 + 5, "Chronoware", 0xF00, 0);
  write(SCREEN_W/2 - 2, SCREEN_H/2 + 6,    "Games"  , 0xFFF, 0);

  events = introEvents;
  tick = introTick;
  redraw = introRedraw;

  while(!quit) {
    events();
    tick();
    redraw();

    SDL_Delay(20);
  }

  deinit();
  return EXIT_SUCCESS;
}