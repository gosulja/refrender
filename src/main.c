#include <stdio.h>
#include <stdlib.h>
#include <glew.h>
#include <glfw3.h>
#include <cglm/cglm.h>

#include "shader.h"
#include "window.h"
#include "object.h"
#include "color4.h"
#include "object_manager.h"
#include "renderer.h"
#include "state.h"
#include "pre.h"

int main() {
    GLFWwindow* window = initializeGLFWWindow();
    if (window == NULL) {
        fprintf(stderr, "Failed to create GLFW window\n");
        return -1;
    }

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW initialization failed: %s\n", glewGetErrorString(err));
        return -1;
    }

    unsigned int shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);
    if (shaderProgram == 0) {
        fprintf(stderr, "Failed to create shader program\n");
        return -1;
    }

    initObjectManager();

    State state;
    initState(&state);

    // Create a red cube
    Object* redCube = createCube(0.5f, (Color4){0.5f, 0.5f, 0.0f, 1.0f}, "../textures/default.png");
    if (redCube == NULL) {
        fprintf(stderr, "Failed to create red cube\n");
        return -1;
    }
    addObject(redCube);

    // Create a green cube
    Object* greenCube = createCube(0.5f, (Color4){0.0f, 1.0f, 0.0f, 1.0f}, "../textures/default.png");
    if (greenCube == NULL) {
        fprintf(stderr, "Failed to create green cube\n");
        return -1;
    }
    glm_translate(greenCube->modelMatrix, (vec3){2.0f, 0.0f, 0.0f});
    addObject(greenCube);

    render(window, shaderProgram, &state);

    cleanupObjectManager();
    glDeleteProgram(shaderProgram);
    glfwTerminate();

    return 0;
}
