#ifndef SHADER_H
#define SHADER_H
#include "primitive.h"

typedef struct ShaderProgram {
    GLuint id, vs_id, fs_id, gs_id;
} ShaderProgram;

#define SHADER_LAST SHADER_LINES
typedef enum ShaderEnum {
    SHADER_NONE=0,
    SHADER_BASIC,
    SHADER_POINTS,
    SHADER_LINES
} ShaderEnum;

ShaderProgram shader_create(char* vs_path, char* fs_path);
ShaderProgram shader_create_with_gs(char* vs_path, char* fs_path, char* gs_path);
void shader_destroy(ShaderProgram self);
void shader_bind(ShaderProgram self);
void shader_unbind();

#endif