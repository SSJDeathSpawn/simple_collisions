#include "renderer.h"
#include <GL/glew.h>
#include <stdio.h>

void init_renderer(Renderer *self) {
    *self = (Renderer) {0};
    self->curr_shader = SHADER_NONE;

    self->all_shaders[SHADER_BASIC] = shader_create("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");
    self->all_shaders[SHADER_POINTS] = shader_create("res/shaders/big_pt_vertex.glsl", "res/shaders/fragment.glsl");
    self->all_shaders[SHADER_LINES] = shader_create_with_gs("res/shaders/vert_ol.glsl", "res/shaders/frag_ol.glsl", "res/shaders/lines.glsl");

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

void load_vbo_ibo_renderer(Renderer *self, Vertex vertices[], int num_vertices, GLuint indices[], int num_indices) {
    self->flag = true;
    vbo_buffer(self->curr_vbo, vertices, 0, sizeof(vertices[0])*num_vertices);
    vbo_buffer(self->curr_ibo, indices, 0, sizeof(indices[0])*num_indices);
    self->points = num_indices;
    vbo_unbind(self->curr_vbo);
    vbo_unbind(self->curr_ibo);
}

void load_vbo_renderer(Renderer* self, Vertex vertices[], int num_vertices) {
    self->flag = false;
    vbo_buffer(self->curr_vbo, vertices, 0, sizeof(vertices[0])*num_vertices);
    self->points = num_vertices;
    vbo_unbind(self->curr_vbo);
}

void load_scene_obj_renderer(Renderer *self, SceneObject scene_obj) {
    if(!scene_obj.noInd) {
        load_vbo_ibo_renderer(self, scene_obj.vert, scene_obj.num_vertices, scene_obj.ind, scene_obj.num_indices);
    } else {
        load_vbo_renderer(self, scene_obj.vert, scene_obj.num_vertices);
    }
    use_shader_renderer(self, scene_obj.shader);
}

void use_shader_renderer(Renderer *self, ShaderEnum shader) {
    if(shader == self->curr_shader) {
        return ;
    }

    self->curr_shader = shader;
    self->sel_shader = self->all_shaders[shader];
    shader_bind(self->sel_shader);
}

void draw_call_renderer(Renderer self, GLenum mode) {
    vao_bind(self.curr_vao);
    if (self.flag) {
        vbo_bind(self.curr_ibo);
        glDrawElements(mode, self.points, GL_UNSIGNED_INT, (void* ) 0);
        vbo_unbind(self.curr_ibo);
    } else {
        glDrawArrays(mode, 0, self.points);
    }
    vao_unbind();
}

void load_vao_attrs(Renderer self, VertexLayout *vl) {
    add_vao_attr_vl(self.curr_vao, self.curr_vbo, vl);
}
