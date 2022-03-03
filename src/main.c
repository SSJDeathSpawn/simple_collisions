#include <GL/glew.h>
#define NO_SDL_GLEXT
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "primitives/shader.h"
#include "primitives/vbo.h"
#include "primitives/vao.h"
#include "utils/error_handling.h"
int main() {
    
    GLfloat vertices[] = {0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 0.5f}; 

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); 
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window* win = SDL_CreateWindow("Collision Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    
    void* ctx = SDL_GL_CreateContext(win);
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    
    if (err != GLEW_OK) {
        printf("Error: %s\n", glewGetErrorString(err));
        SDL_DestroyWindow(win);
        SDL_Quit();
        return -1;
    }

    printf("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("If you can see this, printf is working\n");
    bool running = true; 

    printf("Creating shaders!\n");
    ShaderProgram shader = shader_create("./res/shaders/vertex.glsl","./res/shaders/fragment.glsl");
    VAO vao = vao_create();
    vao_bind(vao);
    VBO vbo = vbo_create(GL_ARRAY_BUFFER);
    vao_bind(vao);
    vbo_buffer(vbo, vertices, 0, sizeof(GLfloat)*6);
    vbo_bind(vbo);
    vao_attr(vao, vbo, 0, 2, GL_FLOAT, 0, 0);
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        glClear(GL_COLOR_BUFFER_BIT);
        shader_bind(shader);
        vao_bind(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        getErrorAndLog();
        vao_unbind(vao);
        shader_unbind();
        SDL_GL_SwapWindow(win);
    } 
    /*vbo_destroy(vbo);
    vao_destroy(vao);
    shader_destroy(shader);*/

    SDL_DestroyWindow(win);
    SDL_Quit(); 
    return 0;
}