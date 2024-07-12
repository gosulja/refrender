#include "object.h"

Object* createObject(float* vertices, int verticesSize, unsigned int* indices, int indicesSize) {
    printf("Starting createObject function\n");

    Object* obj = malloc(sizeof(Object));
    if (obj == NULL) {
        printf("Error: Failed to allocate memory for Object\n");
        return NULL;
    }
    printf("Object allocated successfully\n");

    for (int i = 0; i < 3; i++) {
        obj->position[i] = 0.0f;
        obj->rotation[i] = 0.0f;
        obj->scale[i] = 1.0f;
    }
    for (int i = 0; i < 4; i++) {
        obj->color[i] = 1.0f;
    }
    printf("Object properties initialized\n");

    printf("Generating VAO\n");
    glGenVertexArrays(1, &obj->VAO);
    if (glGetError() != GL_NO_ERROR) {
        printf("Error: Failed to generate VAO\n");
        free(obj);
        return NULL;
    }

    printf("Generating VBO\n");
    glGenBuffers(1, &obj->VBO);
    if (glGetError() != GL_NO_ERROR) {
        printf("Error: Failed to generate VBO\n");
        free(obj);
        return NULL;
    }

    printf("Generating EBO\n");
    glGenBuffers(1, &obj->EBO);
    if (glGetError() != GL_NO_ERROR) {
        printf("Error: Failed to generate EBO\n");
        free(obj);
        return NULL;
    }

    printf("Binding VAO\n");
    glBindVertexArray(obj->VAO);

    printf("Binding and setting up VBO\n");
    glBindBuffer(GL_ARRAY_BUFFER, obj->VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
    if (glGetError() != GL_NO_ERROR) {
        printf("Error: Failed to set up VBO\n");
        free(obj);
        return NULL;
    }

    printf("Binding and setting up EBO\n");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
    if (glGetError() != GL_NO_ERROR) {
        printf("Error: Failed to set up EBO\n");
        free(obj);
        return NULL;
    }

    printf("Setting up vertex attributes\n");
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    if (glGetError() != GL_NO_ERROR) {
        printf("Error: Failed to set up vertex attributes\n");
        free(obj);
        return NULL;
    }

    printf("Unbinding buffers\n");
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    printf("Object created successfully\n");
    return obj;
}

void destroyObject(Object* obj) {
    glDeleteVertexArrays(1, &obj->VAO);
    glDeleteBuffers(1, &obj->VBO);
    glDeleteBuffers(1, &obj->EBO);
    free(obj);
}

