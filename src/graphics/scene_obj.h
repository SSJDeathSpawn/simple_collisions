#ifndef SCENE_OBJ_H
#define SCENE_OBJ_H
#include "../utils/basic.h"
#include "../primitives/shader.h"
#include <stdbool.h>

typedef struct SceneObject {
    ShaderEnum shader;
    Vertex *vert;
    int num_vertices;
    GLuint *ind;
    int num_indices;
    bool noInd; 
} SceneObject;

#endif