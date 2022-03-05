#include <GL/glew.h>
#define NO_SDL_GLEXT
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "graphics/renderer.h"
#include "utils/error_handling.h"
int main() {
    
    unsigned int lastTick, deltaTime;

    Vector2f vertices[] = {
        {-0.75f, -0.75f}, 
        { 0.75f, -0.75f}, 
        { 0.75f,  0.75f}, 
        {-0.75f,  0.75f}
    };
    GLuint indices[] = {
        0, 1, 2,
        2, 3, 0
    };

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

    Renderer renderer;

    init_renderer(&renderer);
    load_vbo_ibo_renderer(&renderer, vertices, 4, indices, 6);
    use_shader_renderer(&renderer, SHADER_LINES);

    lastTick = SDL_GetTicks();
    while (running) {
        deltaTime = SDL_GetTicks() - lastTick;  
        lastTick = SDL_GetTicks();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        //printf("%d\n", deltaTime);
        glClear(GL_COLOR_BUFFER_BIT);
        draw_call_renderer(renderer);
        SDL_GL_SwapWindow(win);
    } 
    destroy_renderer(&renderer);
    SDL_DestroyWindow(win);
    SDL_Quit(); 
    return 0;
}