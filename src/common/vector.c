#include <math.h>

#include "common/vector.h"


// Compute distance between two points in 3D space
float vector_distance(Vector3 a, Vector3 b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
}

void vector_set_to_vector(Vector3 *dest, Vector3 *src) {
    dest->x = src->x;
    dest->y = src->y;
    dest->z = src->z;
}
