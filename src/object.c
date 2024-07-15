#include "object.h"
#include "color4.h"
#include <cglm/cglm.h>

Object* createObject(float* vertices, int verticesSize, unsigned int* indices, int indicesSize, Color4 color) {
    Object* obj = malloc(sizeof(Object));
    if (obj == NULL) {
        printf("Error: Failed to allocate memory for Object\n");
        return NULL;
    }
    
    glm_vec3_zero(obj->position);
    glm_vec3_zero(obj->rotation);
    glm_vec3_one(obj->scale);
    
    glm_vec4_copy((vec4){color.r, color.g, color.b, color.a}, obj->color);

    glm_mat4_identity(obj->modelMatrix);

    glGenVertexArrays(1, &obj->VAO);
    if (glGetError() != GL_NO_ERROR) {
        printf("Error: Failed to generate VAO\n");
        free(obj);
        return NULL;
    }

    glGenBuffers(1, &obj->VBO);
    if (glGetError() != GL_NO_ERROR) {
        printf("Error: Failed to generate VBO\n");
        free(obj);
        return NULL;
    }

    glGenBuffers(1, &obj->EBO);
    if (glGetError() != GL_NO_ERROR) {
        printf("Error: Failed to generate EBO\n");
        free(obj);
        return NULL;
    }

    glBindVertexArray(obj->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, obj->VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
    if (glGetError() != GL_NO_ERROR) {
        printf("Error: Failed to set up VBO\n");
        free(obj);
        return NULL;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
    if (glGetError() != GL_NO_ERROR) {
        printf("Error: Failed to set up EBO\n");
        free(obj);
        return NULL;
    }

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    if (glGetError() != GL_NO_ERROR) {
        printf("Error: Failed to set up vertex attributes\n");
        free(obj);
        return NULL;
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return obj;
}

void destroyObject(Object* obj) {
    glDeleteVertexArrays(1, &obj->VAO);
    glDeleteBuffers(1, &obj->VBO);
    glDeleteBuffers(1, &obj->EBO);
    free(obj);
}

void updateObjectModelMatrix(Object* obj) {
    mat4 translate, rotate, scale, temp;

    glm_mat4_identity(obj->modelMatrix);
    
    glm_translate_make(translate, obj->position);
    
    glm_mat4_identity(rotate);
    glm_rotate(rotate, obj->rotation[0], (vec3){1.0f, 0.0f, 0.0f});
    glm_rotate(rotate, obj->rotation[1], (vec3){0.0f, 1.0f, 0.0f});
    glm_rotate(rotate, obj->rotation[2], (vec3){0.0f, 0.0f, 1.0f});
    
    glm_scale_make(scale, obj->scale);
    
    glm_mat4_mul(translate, rotate, temp);
    glm_mat4_mul(temp, scale, obj->modelMatrix);
}
