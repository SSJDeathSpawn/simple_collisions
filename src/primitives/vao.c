#include "vao.h"

VAO vao_create() {
    VAO self;
    glGenVertexArrays(1, &self.id);
    return self;
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

void vao_unbind() {
    glBindVertexArray(0);
}
