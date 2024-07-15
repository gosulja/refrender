#ifndef OBJECT_H
#define OBJECT_H

#include "color4.h"
#include <glew.h>
#include <cglm/cglm.h>

typedef struct {
    vec3 position;
    vec3 rotation;
    vec3 scale;
    vec4 color;
    mat4 modelMatrix;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    unsigned int texture;
} Object;

Object* createObject(float* vertices, int verticesSize, unsigned int* indices, int indicesSize, Color4 color);
void destroyObject(Object* obj);

void updateObjectModelMatrix(Object* obj);

#endif // !OBJECT_H
