#include <stdio.h>
#include <stdlib.h>
#include <glew.h>
#include <glfw3.h>
#include "shader.h"
#include "window.h"
#include "object.h"
#include "object_manager.h"
#include "renderer.h"

unsigned int createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);

int main() {
    GLFWwindow* window = initializeGLFWWindow();
    printf("Initialized glfw window\n");
    if (window == NULL) {
        fprintf(stderr, "Failed to create GLFW window\n");
        return -1;
    }

    GLenum err = glewInit();
    printf("Initialized glew\n");  
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW initialization failed: %s\n", glewGetErrorString(err));
        return -1;
    }

    unsigned int shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);
    printf("Created shader program\n");  
    if (shaderProgram == 0) {
        fprintf(stderr, "Failed to create shader program\n");
        return -1;
    }

    printf("Initialized object manager\n"); 
    initObjectManager();

    // test
    
    // First square (red)
    float vertices1[] = {
        0.0f,  0.5f, 0.0f,  // top right
        0.0f, -0.5f, 0.0f,  // bottom right
        -1.0f, -0.5f, 0.0f,  // bottom left
        -1.0f,  0.5f, 0.0f   // top left 
    };
    unsigned int indices[] = {
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    printf("Before creating red square\n");
    Object* redSquare = createObject(vertices1, sizeof(vertices1), indices, sizeof(indices));
    printf("Created red square\n");
    if (redSquare == NULL) {
        fprintf(stderr, "Failed to create red square\n");
        return -1;
    }
    // Set color to red
    redSquare->color[0] = 1.0f; // Red
    redSquare->color[1] = 0.0f; // Green
    redSquare->color[2] = 0.0f; // Blue
    redSquare->color[3] = 1.0f; // Alpha

    printf("Add red square to manager\n");
    addObject(redSquare);

    // Second square (blue)
    float vertices2[] = {
        1.0f,  0.5f, 0.0f,  // top right
        1.0f, -0.5f, 0.0f,  // bottom right
        0.0f, -0.5f, 0.0f,  // bottom left
        0.0f,  0.5f, 0.0f   // top left 
    };

    printf("Before creating blue square\n");
    Object* blueSquare = createObject(vertices2, sizeof(vertices2), indices, sizeof(indices));
    printf("Created blue square\n");
    if (blueSquare == NULL) {
        fprintf(stderr, "Failed to create blue square\n");
        return -1;
    }
    // Set color to blue
    blueSquare->color[0] = 0.0f; // Red
    blueSquare->color[1] = 0.0f; // Green
    blueSquare->color[2] = 1.0f; // Blue
    blueSquare->color[3] = 1.0f; // Alpha

    printf("Add blue square to manager\n");
    addObject(blueSquare);

    //test

    printf("Attempting to render objects\n");
    render(window, shaderProgram);

    cleanupObjectManager();
    glDeleteProgram(shaderProgram);
    glfwTerminate();

    return 0;
}

unsigned int createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fprintf(stderr, "Vertex shader compilation failed: %s\n", infoLog);
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        fprintf(stderr, "Fragment shader compilation failed: %s\n", infoLog);
    }

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fprintf(stderr, "Program link failed: %s\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

