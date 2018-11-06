#ifndef STATES__H
#define STATES__H

typedef struct State {
    void (*events)();
    void (*tick)();
    void (*redraw)();
} State;

void setState(State* state);
struct State *currentState;
struct State *nextState;

#endif