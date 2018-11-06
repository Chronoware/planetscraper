#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "render.h"

uint8_t screenW = SCREEN_W, screenH = SCREEN_H;

SDL_Window*   window   = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture*  tileset  = NULL;

uint8_t tileW, tileH, zoom = 2;
uint8_t screen[SCREEN_W * SCREEN_H * 5] = { 0 };


bool init() {
  bool success = true;

  SDL_Surface* tilesetSurface = IMG_Load("tileset.png");
  if(tilesetSurface == NULL) return false;
  
  SDL_SetColorKey(tilesetSurface, SDL_TRUE, SDL_MapRGB(tilesetSurface->format, 255, 0, 255));
  tileW = tilesetSurface->w/16;
  tileH = tilesetSurface->h/16;

  window = SDL_CreateWindow(
    "Planet Scraper", SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    tileW * SCREEN_W * zoom, tileH * SCREEN_H * zoom,
    SDL_WINDOW_SHOWN
  );
  if(window == NULL) return false;

  if(!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    printf("SDL_image Error: %s\n", IMG_GetError());
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if(renderer == NULL) return false;

  tileset = SDL_CreateTextureFromSurface(renderer, tilesetSurface);
  SDL_FreeSurface(tilesetSurface);

  return success;
}

void clearScreen() {
  for(uint16_t i=0; i<SCREEN_H * SCREEN_W * 5; i+=5) screen[i] = 0;
}

void addTile(uint16_t x, uint16_t y, char c, uint16_t fg, uint16_t bg) {
  screen[(y*SCREEN_W + x)*5] = c;
  screen[(y*SCREEN_W + x)*5 +1] = fg >> 8;
  screen[(y*SCREEN_W + x)*5 +2] = fg & 0xFF;
  screen[(y*SCREEN_W + x)*5 +3] = bg >> 8;
  screen[(y*SCREEN_W + x)*5 +4] = bg & 0xFF;
}

void write(uint16_t x, uint16_t y, char* s, uint16_t fg, uint16_t bg) {
  for(int i=0; s[i]; i++) {
    addTile(x+i, y, s[i], fg, bg);
  }
}

bool deinit() {
  SDL_DestroyTexture(tileset);
  SDL_DestroyWindow(window);
  IMG_Quit();
  SDL_Quit();

  return true;
}
