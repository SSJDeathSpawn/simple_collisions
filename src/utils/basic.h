#ifndef BASIC_H
#define BASIC_H

typedef struct Vector2f {
    float x;
    float y;
} Vector2f;

Vector2f add_vectors(Vector2f addend1, Vector2f addend2);

Vector2f sub_vectors(Vector2f minuend, Vector2f subtrahend);

Vector2f scalar_mul(Vector2f vec, float scalar);

float magnitude(Vector2f self); 

float dot_product(Vector2f u, Vector2f v);

#endif