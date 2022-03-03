#ifndef VBO_H
#define VBO_H
#include "primitive.h"

typedef struct VBO {
    GLuint id;
    GLint type;
} VBO;

VBO vbo_create(GLint type);

void vbo_destroy (VBO self);

void vbo_bind(VBO self);

void vbo_buffer(VBO self, void* data, size_t offset, size_t count);

void vbo_unbind(VBO self);

#endif