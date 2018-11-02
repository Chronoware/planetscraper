#ifndef STATES__H
#define STATES__H

typedef struct State {
    void (*events)(void);
    void (*tick)(void);
    void (*redraw)(void);
} State;

void setState(State* state);
struct State *currentState;
struct State *nextState;

#endif