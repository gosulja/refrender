#include "renderer.h"
#include "object_manager.h"

void render(GLFWwindow* window, unsigned int shaderProgram) {
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        ObjectManager* manager = getObjectManager();
        for (int i = 0; i < manager->objectCount; i++) {
            Object* obj = manager->objects[i];

            int colorLoc = glGetUniformLocation(shaderProgram, "objectColor");
            glUniform4fv(colorLoc, 1, obj->color);
            
            glBindVertexArray(obj->VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }
    
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

