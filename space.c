
/*   VARIABLES   */

typedef struct {
    float x;
    float y;
    float z;
} Vector3;

typedef struct {
    float roll;  // rad
    float pitch; // rad
    float yaw;   // rad
    float speed;
} Velocity;

typedef struct {
    Vector3 position;
    float mass; 
    Velocity velocity;
} SpaceObject;

SpaceObject space_objects[4096];




/*   SPACE GENERATION   */

int generate_debris() {

    return 0;
}

int generate_satellites() {

    return 0;
} 




/*   UPDATE   */

int tick() {

    return 0;
}

