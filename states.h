#ifndef STATES__H
#define STATES__H

typedef struct{
    void (*events)(void);
    void (*tick)(void);
    void (*redraw)(void);
} State;

void setState(State* state);
struct State currentState;

#endif