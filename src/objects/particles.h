#ifndef PARTICLES_H
#define PARTICLES_H
#include "../utils/basic.h"
#include "../graphics/scene_obj.h"

typedef struct Particle {
    Vector2f position;
    Vector2f velocity; 
    Colour col;
} Particle;

Particle create_particle( Vector2f position, Vector2f velocity, Colour col);

void tick(Particle self, float delta_time);

void set_velocity(Particle *self, Vector2f new_vel);

float speed(Particle self);

void handle_collision(Particle* p1, Particle* p2);

Particle *create_particles(int number); 

SceneObject make_scene_obj_from_particles(Particle particles[], int number);

#endif