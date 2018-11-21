#ifndef STATEGAME__H
#define STATEGAME__H

void gameEvents();
void gameTick();
void gameRedraw();
struct State gameState;

uint8_t *genChunk(uint8_t x, uint16_t y, uint32_t seed);

#endif