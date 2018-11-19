#ifndef EVENTS__H
#define EVENTS__H

extern bool quit;

void (*events)();
void (*tick)();
void (*redraw)();

#endif