#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H
  
#include "object.h"

#define MAX_OBJECTS 1000

typedef struct {
    Object* objects[MAX_OBJECTS];
    int objectCount;
} ObjectManager;

void initObjectManager();
void addObject(Object* obj);
void cleanupObjectManager();
ObjectManager* getObjectManager();

#endif // !OBJECT_MANAGER_H
