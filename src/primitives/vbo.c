#include "vbo.h"

struct VBO vbo_create(GLint type) {
    struct VBO self = {
        .type=type
    };
    glGenBuffers(1, &self.id);
    return self;
} 

void vbo_destroy(struct VBO self) {
    glDeleteBuffers(1, &self.id);
}

void vbo_bind(struct VBO self) {
    glBindBuffer(self.type, self.id);
}

void vbo_buffer(struct VBO self, void* data, size_t offset, size_t count) {
    vbo_bind(self);
    glBufferData(self.type, count - offset, data, GL_DYNAMIC_DRAW);
    vbo_unbind(self);
}

void vbo_unbind(VBO self) {
    glBindBuffer(self.type, 0);
}
