#include "object_manager.h"
#include <stdlib.h>
#include <stdio.h>

static ObjectManager objectManager;

void initObjectManager() {
    objectManager.objectCount = 0;
    for (int i = 0; i < MAX_OBJECTS; i++) {
        objectManager.objects[i] = NULL;
    }
}

void addObject(Object* obj) {
    if (objectManager.objectCount < MAX_OBJECTS) {
        objectManager.objects[objectManager.objectCount++] = obj;
    } else {
        fprintf(stderr, "Maximum number of objects reached.\n");
    }
}

void cleanupObjectManager() {
    for (int i = 0; i < objectManager.objectCount; i++) {
        destroyObject(objectManager.objects[i]);
    }

    objectManager.objectCount = 0;
}

ObjectManager* getObjectManager() {
    return &objectManager;
}


