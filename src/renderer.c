#include "renderer.h"
#include "object_manager.h"
#include <cglm/cglm.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include "nuklear.h"
#include "nuklear_glfw_gl3.h"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

static struct nk_context *ctx;
static struct nk_colorf bg;

void initNuklear(GLFWwindow* window) {
    ctx = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);
    struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(&atlas);
    nk_glfw3_font_stash_end();

    bg.r = 0.10f;
    bg.g = 0.18f;
    bg.b = 0.24f;
    bg.a = 1.0f;
}

void shutdownNuklear() {
    nk_glfw3_shutdown();
}

void render(GLFWwindow* window, unsigned int shaderProgram, State* state) {
    mat4 view, projection;

    
    if (!ctx) {
        initNuklear(window);
    }

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

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, obj->texture);
            glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);

            glBindVertexArray(obj->VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);
        }

        nk_glfw3_new_frame();
        if (nk_begin(ctx, "refrunder - Debug", nk_rect(50, 50, 300, 400),
            NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
            NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
        {  
            nk_layout_row_dynamic(ctx, 25, 1);
            nk_label(ctx, "Camera Properties", NK_TEXT_CENTERED);
        
            if (nk_tree_push(ctx, NK_TREE_TAB, "Position", NK_MAXIMIZED)) {
              nk_layout_row_dynamic(ctx, 25, 2);
              nk_label(ctx, "X:", NK_TEXT_LEFT);
              nk_slider_float(ctx, -10.0f, &state->camera.position[0], 10.0f, 0.1f);
              nk_label(ctx, "Y:", NK_TEXT_LEFT);
              nk_slider_float(ctx, -10.0f, &state->camera.position[1], 10.0f, 0.1f);
              nk_label(ctx, "Z:", NK_TEXT_LEFT);
              nk_slider_float(ctx, -10.0f, &state->camera.position[2], 10.0f, 0.1f);
              nk_tree_pop(ctx);
            }

            if (nk_tree_push(ctx, NK_TREE_TAB, "Front", NK_MAXIMIZED)) {
              nk_layout_row_dynamic(ctx, 25, 2);
              nk_label(ctx, "X:", NK_TEXT_LEFT);
              nk_slider_float(ctx, -1.0f, &state->camera.front[0], 1.0f, 0.01f);
              nk_label(ctx, "Y:", NK_TEXT_LEFT);
              nk_slider_float(ctx, -1.0f, &state->camera.front[1], 1.0f, 0.01f);
              nk_label(ctx, "Z:", NK_TEXT_LEFT);
              nk_slider_float(ctx, -1.0f, &state->camera.front[2], 1.0f, 0.01f);
              nk_tree_pop(ctx);
            }

            if (nk_tree_push(ctx, NK_TREE_TAB, "Up", NK_MAXIMIZED)) {
              nk_layout_row_dynamic(ctx, 25, 2);
              nk_label(ctx, "X:", NK_TEXT_LEFT);
              nk_slider_float(ctx, -1.0f, &state->camera.up[0], 1.0f, 0.01f);
              nk_label(ctx, "Y:", NK_TEXT_LEFT);
              nk_slider_float(ctx, -1.0f, &state->camera.up[1], 1.0f, 0.01f);
              nk_label(ctx, "Z:", NK_TEXT_LEFT);
              nk_slider_float(ctx, -1.0f, &state->camera.up[2], 1.0f, 0.01f);
              nk_tree_pop(ctx);
            }

            if (nk_tree_push(ctx, NK_TREE_TAB, "Right", NK_MAXIMIZED)) {
              nk_layout_row_dynamic(ctx, 25, 2);
              nk_label(ctx, "X:", NK_TEXT_LEFT);
              nk_slider_float(ctx, -1.0f, &state->camera.right[0], 1.0f, 0.01f);
              nk_label(ctx, "Y:", NK_TEXT_LEFT);
              nk_slider_float(ctx, -1.0f, &state->camera.right[1], 1.0f, 0.01f);
              nk_label(ctx, "Z:", NK_TEXT_LEFT);
              nk_slider_float(ctx, -1.0f, &state->camera.right[2], 1.0f, 0.01f);
              nk_tree_pop(ctx);
            }

            nk_layout_row_dynamic(ctx, 25, 2);
            nk_label(ctx, "Yaw:", NK_TEXT_LEFT);
            nk_slider_float(ctx, -360.0f, &state->camera.yaw, 360.0f, 1.0f);
            nk_label(ctx, "Pitch:", NK_TEXT_LEFT);
            nk_slider_float(ctx, -89.0f, &state->camera.pitch, 89.0f, 1.0f); 
        }
        nk_end(ctx);
        
        nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    
    shutdownNuklear();
}

