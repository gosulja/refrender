#ifndef OBJECT_H
#define OBJECT_H

#include <glew.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float position[3];
    float rotation[3];
    float scale[3];
    float color[4];

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
} Object;

Object* createObject(float* vertices, int verticesSize, unsigned int* indices, int indicesSize);
void destroyObject(Object* obj);

#endif // !OBJECT_H
