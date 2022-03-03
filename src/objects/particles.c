#include "particles.h"

struct Particle create_particle( Vector2f position, Vector2f velocity) {
    return (Particle) {position, velocity}; 
}

void tick(Particle self, float delta_time) {
    self.position = add_vectors(self.position, scalar_mul(self.velocity, delta_time));
    
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