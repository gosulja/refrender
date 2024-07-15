#ifndef RENDERER_H
#define RENDERER_H

#include <glew.h>
#include <glfw3.h>
#include "state.h"
#include "window.h"

void render(GLFWwindow* window, unsigned int shaderProgram, State* state);

#endif // !RENDERER_H
