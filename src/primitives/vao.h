#ifndef VAO_H
#define VAO_H

#include "primitive.h"
#include "vbo.h"

typedef struct VAO {
    GLuint id;
} VAO;

VAO vao_create();

void vao_destroy(VAO self);
void vao_bind(VAO self);
void vao_attr(VAO self, VBO vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);
void vao_unbind();

#endif