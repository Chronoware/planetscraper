#ifndef STATENEWGAME__H
#define STATENEWGAME__H

void newgameEvents();
void newgameTick();
void newgameRedraw();
void worldGen(FILE *fp);
struct State newgameState;

#endif