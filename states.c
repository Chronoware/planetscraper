#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "states.h"
#include "events.h"
#include "tick.h"
#include "render.h"

void setState(State* state) {
  currentState = state;
}