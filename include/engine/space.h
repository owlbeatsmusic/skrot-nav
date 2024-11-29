#ifndef SPACE_H_
#define SPACE_H_

#include "common/vector.h"

typedef enum {
    DEBRIS,
    SPACECRAFT
} SpaceObjectType;

typedef struct {
    SpaceObjectType type;
    Vector3 position;
    Vector3 velocity;
    float mass; 
    float radius;
} SpaceObject;

extern const float G;
extern const float M;
extern const float DELTA_T;
extern const float EARTH_RADIUS;

extern const int MAX_SPACEOBJECTS;
extern SpaceObject spaceobjects[];

extern int space_append_spaceobject(SpaceObjectType type, Vector3 position, Vector3 velocity, float mass);

extern int space_start(void);

#endif

