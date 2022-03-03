//Simulation for the things I've created
#include <stdio.h>
#include "objects/particles.h"
#include "utils/basic.h"
#include <math.h>
int main() {
    Vector2f pos1 =  (Vector2f) {.x = (float) sqrt(2), .y = 0};
    Vector2f vel1 = (Vector2f) {.x = 0, .y=2};    
    Vector2f pos2 = (Vector2f) {.x = 0, .y = (float) sqrt(2)};
    Vector2f vel2 = (Vector2f) {.x = 0, .y =-2};
    Particle p1 = create_particle(pos1, vel1);
    Particle p2 = create_particle(pos2, vel2);
    fprintf(stdout, "Before collision:\n");
    fprintf(stdout, "Particle 1's velocity: %.2fi + %.2fj\n", p1.velocity.x, p1.velocity.y);    
    fprintf(stdout, "Particle 2's velocity: %.2fi + %.2fj\n", p2.velocity.x, p2.velocity.y);

    handle_collision(&p1, &p2);

    fprintf(stdout, "After collision:\n");
    fprintf(stdout, "Particle 1's veclocity: %.2fi + %.2fj\n", p1.velocity.x, p1.velocity.y);
    fprintf(stdout, "Particle 2's veclocity: %.2fi + %.2fj\n", p2.velocity.x, p2.velocity.y);
}