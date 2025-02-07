#ifndef VECTOR_H_
#define VECTOR_H_

typedef struct {
    float x;
    float y;
    float z;
} Vector3;

Vector3 vector_cross_product(Vector3 a, Vector3 b);
float vector_magnitude(Vector3 v);
Vector3 vector_normalize(Vector3 v);
extern float vector_distance(Vector3 a, Vector3 b);
extern void vector_set_to_vector(Vector3 *dest, Vector3 *src);

#endif
