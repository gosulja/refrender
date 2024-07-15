#include "camera.h"
#include <math.h>

void initCamera(Camera* camera) {
    glm_vec3_copy((vec3){0.0f, 0.0f, 3.0f}, camera->position);
    glm_vec3_copy((vec3){0.0f, 0.0f, -1.0f}, camera->front);
    glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, camera->up);
    glm_vec3_copy((vec3){1.0f, 0.0f, 0.0f}, camera->right);
    camera->yaw = -90.0f;
    camera->pitch = 0.0f;
    updateCamera(camera);
}

void updateCamera(Camera* camera) {
    vec3 front;
    front[0] = cos(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    front[1] = sin(glm_rad(camera->pitch));
    front[2] = sin(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    glm_vec3_normalize_to(front, camera->front);
    
    glm_vec3_cross(camera->front, (vec3){0.0f, 1.0f, 0.0f}, camera->right);
    glm_vec3_normalize(camera->right);
    
    glm_vec3_cross(camera->right, camera->front, camera->up);
    glm_vec3_normalize(camera->up);
}
