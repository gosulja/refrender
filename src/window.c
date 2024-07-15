#include "window.h"
#include "state.h"
#include <stdio.h>

GLFWwindow* initializeGLFWWindow() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW.\n");
        return NULL;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "rufrender", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to create window.\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
        glfwTerminate();
        return NULL;
    }

    return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window, State *state) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);

    float cameraSpeed = state->camSpeed * state->deltaTime;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        glm_vec3_muladd(state->camera.front, (vec3){cameraSpeed, cameraSpeed, cameraSpeed}, state->camera.position);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        glm_vec3_muladd(state->camera.front, (vec3){-cameraSpeed, -cameraSpeed, -cameraSpeed}, state->camera.position);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        glm_vec3_muladd(state->camera.right, (vec3){-cameraSpeed, -cameraSpeed, -cameraSpeed}, state->camera.position);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        glm_vec3_muladd(state->camera.right, (vec3){cameraSpeed, cameraSpeed, cameraSpeed}, state->camera.position);

    updateCamera(&state->camera);
}
