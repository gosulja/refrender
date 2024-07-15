#include "pre.h"
#include <stdlib.h>

Object* createCube(float size, Color4 color, const char* texturePath) {
    float vertices[] = {
        // positions          // texture coords
        // back face
        -size, -size, -size,  0.0f, 0.0f, // tottom left
         size, -size, -size,  1.0f, 0.0f, // bottom right
         size,  size, -size,  1.0f, 1.0f, // top right
         size,  size, -size,  1.0f, 1.0f, // top right
        -size,  size, -size,  0.0f, 1.0f, // top left
        -size, -size, -size,  0.0f, 0.0f, // bottom left
        // front face
        -size, -size,  size,  0.0f, 0.0f, // bottom left
         size, -size,  size,  1.0f, 0.0f, // bottom right
         size,  size,  size,  1.0f, 1.0f, // top right
         size,  size,  size,  1.0f, 1.0f, // top right
        -size,  size,  size,  0.0f, 1.0f, // top left
        -size, -size,  size,  0.0f, 0.0f, // bottom left
        // left face
        -size,  size,  size,  1.0f, 0.0f, // top right
        -size,  size, -size,  1.0f, 1.0f, // top left
        -size, -size, -size,  0.0f, 1.0f, // bottom left
        -size, -size, -size,  0.0f, 1.0f, // bottom left
        -size, -size,  size,  0.0f, 0.0f, // bottom right
        -size,  size,  size,  1.0f, 0.0f, // top right
        // right face
         size,  size,  size,  1.0f, 0.0f, // top left
         size,  size, -size,  1.0f, 1.0f, // top right
         size, -size, -size,  0.0f, 1.0f, // bottom right
         size, -size, -size,  0.0f, 1.0f, // bottom right
         size, -size,  size,  0.0f, 0.0f, // bottom left
         size,  size,  size,  1.0f, 0.0f, // top left
        // bottom face
        -size, -size, -size,  0.0f, 1.0f, // top right
         size, -size, -size,  1.0f, 1.0f, // top left
         size, -size,  size,  1.0f, 0.0f, // bottom left
         size, -size,  size,  1.0f, 0.0f, // bottom left
        -size, -size,  size,  0.0f, 0.0f, // bottom right
        -size, -size, -size,  0.0f, 1.0f, // top right
        // top face
        -size,  size, -size,  0.0f, 1.0f, // top left
         size,  size, -size,  1.0f, 1.0f, // top right
         size,  size,  size,  1.0f, 0.0f, // bottom right
         size,  size,  size,  1.0f, 0.0f, // bottom right
        -size,  size,  size,  0.0f, 0.0f, // bottom left
        -size,  size, -size,  0.0f, 1.0f  // top left
    };
    
    return createObject(vertices, sizeof(vertices), NULL, 0, color, texturePath);
}
