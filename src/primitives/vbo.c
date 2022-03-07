#include "vbo.h"

VBO vbo_create(GLint type) {
    VBO self = {
        .type=type
    };
    glGenBuffers(1, &self.id);
    return self;
} 

void vbo_destroy(VBO self) {
    glDeleteBuffers(1, &self.id);
}

void vbo_bind(VBO self) {
    glBindBuffer(self.type, self.id);
}

void vbo_buffer(VBO self, void* data, size_t offset, size_t count) {
    vbo_bind(self);
    glBufferData(self.type, count - offset, data, GL_DYNAMIC_DRAW);
    vbo_unbind(self);
}

void vbo_unbind(VBO self) {
    glBindBuffer(self.type, 0);
}
