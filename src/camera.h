#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>

typedef struct {
   vec3 position;
   vec3 front;
   vec3 up;
   float yaw;
   float pitch;
} Camera;

void initCamera(Camera* camera);
void updateCamera(Camera* camera);

#endif // CAMERA_H
