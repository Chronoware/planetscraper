#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "states.h"
#include "events.h"
#include "tick.h"
#include "render.h"
#include "stateIntro.h"

#define TICK 20 // tick length in milliseconds

int main(int argc, char** argv) {
  if(!init()) {
    printf("0 SDL_Error: %s\n", SDL_GetError());
    return 1;
  }

  nextState = &introState;

  uint32_t timestamp;

  while(!quit) {
    timestamp = SDL_GetTicks();
    if(nextState != NULL) {
      setState(nextState);
      nextState = NULL;
    }

    currentState->events();
    currentState->tick();
    currentState->redraw();

    tickNo++;
    while(SDL_GetTicks() - timestamp < TICK) SDL_Delay(1);
  }

  deinit();
  return EXIT_SUCCESS;
}