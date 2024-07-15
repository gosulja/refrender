#ifndef STATE_H
#define STATE_H

#include "camera.h"

typedef struct {
    Camera camera;
    float camSpeed;
    float deltaTime;
    float lastFrame;
} State;

void initState(State* state);

#endif // STATE_H
