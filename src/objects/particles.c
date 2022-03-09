#include "particles.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <malloc.h>

struct Particle create_particle( Vector2f position, Vector2f velocity, Colour col) {
    return (Particle) {position, velocity, col}; 
}

void tick(Particle *self, float delta_time) {
    self->position = add_vectors(self->position, scalar_mul(self->velocity, delta_time));
    if (self->position.x >= 0.75 || self->position.x <= -0.75 || self->position.y >= 0.75 || self->position.y <= -0.75) {
        WallCollisionSide side;
        if(self->position.x >= 0.75 || self->position.x <= -0.75) {
            if (self->position.y >= 0.75 || self->position.y <= -0.75) {
                side = CORNER;
            }
            else if(self->position.x >= 0.75) {
                side = EAST;
            } else {
                side = WEST;
            }
        } 
        else if(self->position.y <= -0.75) {
            side = NORTH;
        } else {
            side = SOUTH;
        }
        particle_collide_wall(self, side);
    }
}

void check_for_collisions(Particle *particles, int num_particles) {
    for (int i=0;i<num_particles;i++) {
        for (int j=i;j<num_particles;j++) {
            if (i!=j) {
                if (magnitude(sub_vectors(particles[i].position, particles[j].position)) <= 0.04f) {
                    handle_collision(&particles[i], &particles[j]);
                }
            }
        }
    }
}

void particle_collide_wall(Particle *self, WallCollisionSide side) {
    switch(side) {
        case NORTH:
            self->velocity = (Vector2f) {self->velocity.x, fabs(self->velocity.y)};
            break;
        case SOUTH:
            self->velocity = (Vector2f) {self->velocity.x, -fabs(self->velocity.y)};
            break;
        case EAST:
            self->velocity = (Vector2f) {-fabs(self->velocity.x), self->velocity.y};
            break;
        case WEST:
            self->velocity = (Vector2f) {fabs(self->velocity.x), self->velocity.y};
            break;
        case CORNER:
            self->velocity = (Vector2f) {-self->velocity.x, -self->velocity.y};
            break; 
    }
}

void set_velocity(Particle *self, Vector2f new_vel) {
    self->velocity = new_vel;
}

float speed(Particle self) {
    return (float) sqrt((double) self.velocity.x*self.velocity.x + self.velocity.y*self.velocity.y);
}

void handle_collision(Particle* p1, Particle* p2) {
    //Components along collision line and perpendicular for p1
    Vector2f line_p1_p2 = sub_vectors(p1->position, p2->position);
    Vector2f unit_line_p1_p2 = scalar_mul(line_p1_p2, 1/magnitude(line_p1_p2));
    Vector2f speed_p1_p2 =scalar_mul(unit_line_p1_p2, (dot_product(p1->velocity, line_p1_p2) / magnitude(line_p1_p2)));
    Vector2f const_p1 = sub_vectors(p1->velocity, speed_p1_p2);

    //Components along collision line and perpendicular for p2 
    Vector2f line_p2_p1 = sub_vectors(p2->position, p1->position);
    Vector2f unit_line_p2_p1 = scalar_mul(line_p2_p1, 1/magnitude(line_p2_p1));
    Vector2f speed_p2_p1 =scalar_mul(unit_line_p2_p1, (dot_product(p2->velocity, line_p2_p1) / magnitude(line_p2_p1)));
    Vector2f const_p2 = sub_vectors(p2->velocity, speed_p2_p1);

    Vector2f new_speed_p1 = add_vectors(const_p1, speed_p2_p1);
    Vector2f new_speed_p2 = add_vectors(const_p2, speed_p1_p2);

    p1->velocity = new_speed_p1;
    p2->velocity = new_speed_p2;
}

Particle *create_particles(int number) {
    Particle *particles = malloc(sizeof(Particle)*number);
    srand(time(NULL));
    for(int i=0;i<number;i++) {
        float max_pos = 0.74f;
        float max_vel = 0.0003f;
        //srand(time(NULL));
        float pos_x = pow(-1, rand()) * ((float)rand()/(float)(RAND_MAX)) * max_pos;
        //srand(time(NULL));
        float pos_y = pow(-1, rand()) * ((float)rand()/(float)(RAND_MAX)) * max_pos;
        //srand(time(NULL));
        float vel_x = pow(-1, rand()) * ((float)rand()/(float)(RAND_MAX)) * max_vel;
        float vel_y = pow(-1, rand()) * (float)sqrt(max_vel*max_vel-vel_x*vel_x); 

        Colour col;
        //srand(time(NULL));
        col.r =((float)rand()/(float)(RAND_MAX));
        //srand(time(NULL));
        col.g =((float)rand()/(float)(RAND_MAX));
        //srand(time(NULL));
        col.b =((float)rand()/(float)(RAND_MAX));
        col.a =((float)rand()/(float)(RAND_MAX));
        
        particles[i] = (Particle){.position = {pos_x, pos_y}, .velocity= {vel_x, vel_y}, .col=col};
    }
    return particles;
}

SceneObject make_scene_obj_from_particles(Particle particles[], int number) {
    SceneObject scene_obj;
    scene_obj.vert = malloc(sizeof(Vertex)*number);
    for(int i=0;i<number;i++) {
        scene_obj.vert[i] = (Vertex) {particles[i].position, particles[i].col};
    }
    scene_obj.noInd=true;
    scene_obj.num_vertices = number;
    scene_obj.shader = SHADER_POINTS;
    return scene_obj; 
}