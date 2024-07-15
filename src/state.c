#include "state.h"

void initState(State* state) {
    initCamera(&state->camera);
    state->camSpeed = 2.5f;
    state->deltaTime = 0.0f;
    state->lastFrame = 0.0f;
}

