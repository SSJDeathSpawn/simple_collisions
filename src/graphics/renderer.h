#ifndef RENDERER_H
#define RENDERER_H
#include "../primitives/vao.h"
#include "../primitives/vbo.h"
#include "../primitives/shader.h"
#include "scene_obj.h"
#include "../utils/basic.h"
#include <stdbool.h>

typedef struct Renderer {
    VBO curr_vbo, curr_ibo;
    VAO curr_vao;    
    ShaderProgram all_shaders[SHADER_LAST+1];
    ShaderEnum curr_shader; 
    ShaderProgram sel_shader;
    bool flag;
    GLuint points;
} Renderer;

void init_renderer(Renderer* self);
void destroy_renderer(Renderer* self);
void load_vbo_ibo_renderer(Renderer *self, Vertex vertices[], int num_vertices, GLuint indices[], int num_indices);
void load_vbo_renderer(Renderer *self, Vertex vertices[], int num_vertices);
void load_scene_obj_renderer(Renderer *self, SceneObject scene_obj);
void use_shader_renderer(Renderer *self, ShaderEnum shader);
void draw_call_renderer(Renderer self, GLenum mode);
void load_vao_attrs(Renderer self, VertexLayout *vl);

#endif
