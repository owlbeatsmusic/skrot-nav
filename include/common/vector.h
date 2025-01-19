#ifndef VECTOR_H_
#define VECTOR_H_

typedef struct {
    float x;
    float y;
    float z;
} Vector3;


extern float vector_distance(Vector3 a, Vector3 b);
extern void vector_set_to_vector(Vector3 *dest, Vector3 *src);

#endif
