#ifndef WINDOW_H
#define WINDOW_H

#include <glew.h>
#include <glfw3.h>

#define WIDTH 1200
#define HEIGHT 600

GLFWwindow* initializeGLFWWindow();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

#endif // !WINDOW_H

