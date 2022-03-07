#ifndef VAO_H
#define VAO_H

#include "primitive.h"
#include "vbo.h"

typedef struct VertexLayout {
    int counter;
    GLsizei stride;
    GLint sizes[];
} VertexLayout;

typedef struct VAO {
    GLuint id;
} VAO;

VAO vao_create();

void add_element_vl(VertexLayout* self, GLint size);

void vao_destroy(VAO self);
void vao_bind(VAO self);
void vao_attr(VAO self, VBO vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);
void add_vao_attr_vl(VAO self, VBO vbo, VertexLayout *vl);
void vao_unbind();

#endif