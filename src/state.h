#ifndef STATE_H
#define STATE_H

#include "camera.h"

typedef struct {
    Camera camera;
} State;

void initState(State* state);

#endif // STATE_H
