/*
    VECTOR.C

    This file contains helper functions for 3D 
    vector calculations.

    (description updated: 2025-02-07)
*/

#include <math.h>

#include "common/vector.h"

Vector3 vector_cross_product(Vector3 a, Vector3 b) {
    return (Vector3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

float vector_magnitude(Vector3 v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Vector3 vector_normalize(Vector3 v) {
    float magnitude = vector_magnitude(v);
    return (Vector3){v.x / magnitude, v.y / magnitude, v.z / magnitude};
}

// Compute distance between two points in 3D space
float vector_distance(Vector3 a, Vector3 b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
}

void vector_set_to_vector(Vector3 *dest, Vector3 *src) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
}
