#ifndef PARTICLES_H
#define PARTICLES_H
#include "../utils/basic.h"

typedef struct Particle {
    struct Vector2f position;
    struct Vector2f velocity; 
} Particle;

Particle create_particle( Vector2f position, Vector2f velocity);

void tick( Particle self, float delta_time);

void set_velocity( Particle self, Vector2f new_vel);

void speed(Particle self);

void handle_collision(Particle* p1, Particle* p2);

#endif