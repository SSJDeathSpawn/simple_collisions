#include "renderer.h"
#include <GL/glew.h>
#include <stdio.h>

void init_renderer(Renderer *self) {
    *self = (Renderer) {0};
    self->curr_shader = SHADER_NONE;

    self->all_shaders[SHADER_BASIC] = shader_create("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");
    self->all_shaders[SHADER_LINES] = shader_create_with_gs("res/shaders/vertex.glsl", "res/shaders/fragment.glsl", "res/shaders/lines.glsl");

    self->curr_vao = vao_create();
    self->curr_vbo = vbo_create(GL_ARRAY_BUFFER);
    self->curr_ibo = vbo_create(GL_ELEMENT_ARRAY_BUFFER);
    self->flag = false;
}

void destroy_renderer(Renderer *self) {
    for (size_t i =0;i<=SHADER_LAST;i++) {
        shader_destroy(self->all_shaders[i]);
    }
    vao_destroy(self->curr_vao);
    vbo_destroy(self->curr_vbo);
    vbo_destroy(self->curr_ibo);

}

void load_vbo_ibo_renderer(Renderer *self, Vector2f vertices[], int num_vertices, GLuint indices[], int num_indices) {
    self->flag = true;
    vbo_buffer(self->curr_vbo, vertices, 0, sizeof(vertices[0])*num_vertices);
    vbo_buffer(self->curr_ibo, indices, 0, sizeof(indices[0])*num_indices);
    self->points = num_indices;
    vao_attr(self->curr_vao, self->curr_vbo, 0, 2, GL_FLOAT, 0, 0);
    vao_unbind();
    vbo_unbind(self->curr_vbo);
    vbo_unbind(self->curr_ibo);
}

void load_vbo_renderer(Renderer* self, Vector2f vertices[], int num_vertices) {
    self->flag = false;
    vbo_buffer(self->curr_vbo, vertices, 0, num_vertices);
    vao_attr(self->curr_vao, self->curr_vbo, 0, 2, GL_FLOAT, 0, 0);
    self->points = num_vertices;
    vao_unbind();
    vbo_unbind(self->curr_vbo);
}

void use_shader_renderer(Renderer *self, ShaderEnum shader) {
    if(shader == self->curr_shader) {
        return ;
    }

    self->curr_shader = shader;
    self->sel_shader = self->all_shaders[shader];
}

void draw_call_renderer(Renderer self) {
    shader_bind(self.sel_shader);
    vao_bind(self.curr_vao);
    if (self.flag) {
        //printf("Hello, drawing %d points\n", self.points);
        vbo_bind(self.curr_ibo);
        glDrawElements(GL_TRIANGLES, self.points, GL_UNSIGNED_INT, (void* ) 0);
        vbo_unbind(self.curr_ibo);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, self.points);
    }
    vao_unbind();
    shader_unbind();
}
