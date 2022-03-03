#ifndef SHADER_H
#define SHADER_H
#include "primitive.h"

typedef struct ShaderProgram {
    GLuint id, vs_id, fs_id;
} ShaderProgram;

ShaderProgram shader_create(char* vs_path, char* fs_path);
void shader_destroy(ShaderProgram self);
void shader_bind(ShaderProgram self);
void shader_unbind();

#endif