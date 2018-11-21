#ifndef STATEGAME__H
#define STATEGAME__H

void gameEvents();
void gameTick();
void gameRedraw();
struct State gameState;

FILE *fp;
extern uint8_t *chunks[256];

uint8_t *loadChunk(uint8_t x, uint8_t y, uint32_t seed);

#endif