#include "vao.h"

VAO vao_create() {
    VAO self;
    glGenVertexArrays(1, &self.id);
    return self;
}

void add_element_vl(VertexLayout* self, GLint size) {
    self->sizes[self->counter] = size;
    self->stride += sizeof(GLfloat) * size;
    self->counter += 1;
}

void vao_destroy(VAO self) {
    glDeleteVertexArrays(1, &self.id);
}

void vao_bind(VAO self) {
    glBindVertexArray(self.id);
}

void vao_attr(VAO self, VBO vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset) {
    vao_bind(self);
    vbo_bind(vbo);
    glEnableVertexAttribArray(index);
    switch(type) {
        case GL_BYTE:
        case GL_UNSIGNED_BYTE:
        case GL_SHORT:
        case GL_UNSIGNED_SHORT:
        case GL_INT:
        case GL_UNSIGNED_INT:
        case GL_INT_2_10_10_10_REV:
        case GL_UNSIGNED_INT_2_10_10_10_REV:
            glVertexAttribIPointer(index, size, type, stride, (void *) offset);
            break;
        default:
            glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void *) offset);
            break; 
    }
    vbo_unbind(vbo);
    vao_unbind();
}

void add_vao_attr_vl(VAO self, VBO vbo, VertexLayout *vl) {
    int offset = 0;
    for(int i=0;i<vl->counter;i++) {
        vao_attr(self, vbo, i, vl->sizes[i], GL_FLOAT, vl->stride, offset);
        offset += vl->sizes[i] * sizeof(GLfloat);
    }
}

void vao_unbind() {
    glBindVertexArray(0);
}
