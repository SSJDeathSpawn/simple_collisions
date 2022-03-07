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

void tick(Particle self, float delta_time) {
    self.position = add_vectors(self.position, scalar_mul(self.velocity, delta_time));
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
        float max_vel = 0.25;
        //srand(time(NULL));
        float pos_x = pow(-1, rand()) * ((float)rand()/(float)(RAND_MAX)) * max_pos;
        //srand(time(NULL));
        float pos_y = pow(-1, rand()) * ((float)rand()/(float)(RAND_MAX)) * max_pos;
        //srand(time(NULL));
        float vel_x = pow(-1, rand()) * ((float)rand()/(float)(RAND_MAX)) * max_vel;
        float vel_y = pow(-1, rand()) * (float)sqrt(0.25*0.25-vel_x*vel_x); 

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