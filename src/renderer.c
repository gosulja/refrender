#include "renderer.h"
#include "object_manager.h"
#include <cglm/cglm.h>

void render(GLFWwindow* window, unsigned int shaderProgram, State* state) {
    mat4 view, projection;

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        state->deltaTime = currentFrame - state->lastFrame;
        state->lastFrame = currentFrame;

        processInput(window, state);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glUseProgram(shaderProgram);

        vec3 cameraTarget;
        glm_vec3_add(state->camera.position, state->camera.front, cameraTarget);
        glm_lookat(state->camera.position, cameraTarget, state->camera.up, view);
        glm_perspective(glm_rad(45.0f), 800.0f / 600.0f, 0.1f, 100.0f, projection);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, (float*)view);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, (float*)projection);

        ObjectManager* manager = getObjectManager();
        for (int i = 0; i < manager->objectCount; i++) {
            Object* obj = manager->objects[i];

            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, (float*)obj->modelMatrix);
            glUniform4fv(glGetUniformLocation(shaderProgram, "objectColor"), 1, obj->color);
            
            glBindVertexArray(obj->VAO);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

