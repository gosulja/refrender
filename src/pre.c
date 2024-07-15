#include "pre.h"
#include <stdlib.h>

Object* createCube(float size, Color4 color) {
    float vertices[] = {
        -size, -size, size,
        size, -size, size,
        size, size, size,
        -size, size, size,

        -size, -size, -size,
        -size, size, -size,
        size, size, -size,
        size, -size, -size,

        -size,  size, -size,
        -size,  size,  size,
         size,  size,  size,
         size,  size, -size,
        
        -size, -size, -size,
         size, -size, -size,
         size, -size,  size,
        -size, -size,  size,
      
        -size, -size, -size,
        -size, -size,  size,
        -size,  size,  size,
        -size,  size, -size,
      
         size, -size, -size,
         size,  size, -size,
         size,  size,  size,
         size, -size,  size
    };

    unsigned int indices[] = {
        0,  1,  2,  2,  3,  0,  // front face
        4,  5,  6,  6,  7,  4,  // back face
        8,  9, 10, 10, 11,  8,  // top face
        12, 13, 14, 14, 15, 12, // bottom face
        16, 17, 18, 18, 19, 16, // left face
        20, 21, 22, 22, 23, 20  // right face
    };

    return createObject(vertices, sizeof(vertices), indices, sizeof(indices), color);
}

