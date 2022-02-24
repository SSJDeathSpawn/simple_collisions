#include <GL/glew.h>
#define NO_SDL_GLEXT
#include <SDL2/SDL.h>
#include <stdio.h>
int main() {
    printf("Starting program");
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("Error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); 
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_Window* win = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
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
    SDL_DestroyWindow(win);
    SDL_Quit(); 
    return 0;
}