#include <GL/glew.h>
#define NO_SDL_GLEXT
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "graphics/renderer.h"
#include "utils/error_handling.h"
#include "graphics/scene_obj.h"
#include "objects/particles.h"

#define PARTICLE_AMT 20

int main(int argc, char** argv) {
    
    unsigned int lastTick, deltaTime;

    Vertex vertices[4] = {
        {{-0.75f, -0.75f}, {1.0f, 0.5f, 0.2f, 1.0f}}, 
        {{ 0.75f, -0.75f}, {1.0f, 0.5f, 0.2f, 1.0f}},
        {{ 0.75f,  0.75f}, {1.0f, 0.5f, 0.2f, 1.0f}},
        {{-0.75f,  0.75f}, {1.0f, 0.5f, 0.2f, 1.0f}}
    };

    VertexLayout *vl;
    vl = (VertexLayout *) malloc(sizeof(VertexLayout) + 2*sizeof(GLint)); 
    vl->counter = 0;
    add_element_vl(vl, 2);
    add_element_vl(vl, 4);
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

    bool running = true; 

    Renderer renderer;
    SceneObject box;
    box.shader = SHADER_LINES;
    box.vert = &vertices;
    box.num_vertices = sizeof(vertices)/sizeof(Vertex); 
    box.ind = &indices;
    box.num_indices = sizeof(indices)/sizeof(GLuint);
    box.noInd = false;

    Particle *particles = create_particles(PARTICLE_AMT);
    Vertex vertexArray[PARTICLE_AMT];

    init_renderer(&renderer);

    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    SDL_GL_SetSwapInterval(1);
    lastTick = SDL_GetTicks();
    while (running) {
        deltaTime = (SDL_GetTicks() - lastTick);  
        lastTick = SDL_GetTicks();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        for (int i=0;i<PARTICLE_AMT;i++) { 
            tick(&particles[i], deltaTime);
        }
        check_for_collisions(particles, PARTICLE_AMT); 
        SceneObject vis_part = make_scene_obj_from_particles(particles, PARTICLE_AMT);
        load_scene_obj_renderer(&renderer, box);
        load_vao_attrs(renderer, vl);
        draw_call_renderer(renderer, GL_TRIANGLES);
        load_scene_obj_renderer(&renderer, vis_part);
        load_vao_attrs(renderer, vl);
        draw_call_renderer(renderer, GL_POINTS);
        getErrorAndLog();
        SDL_GL_SwapWindow(win);
    } 
    destroy_renderer(&renderer);
    SDL_DestroyWindow(win);
    SDL_Quit(); 
    return 0;
}