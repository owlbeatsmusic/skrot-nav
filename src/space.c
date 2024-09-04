#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*   VARIABLES   */

const float G =  6.67e-11;
const float M = 5.977e24;
const float DELTA_T = 1.0;

typedef struct {
    float x;
    float y;
    float z;
} Vector3;

Vector3 earth_pos = {0, 0, 0};

typedef struct {
    Vector3 position;
    Vector3 velocity;
    float mass; 
} SpaceObject;

SpaceObject space_objects[24576];





/*   SPACE    */

// Compute distance between two points in 3D space
float distance(Vector3 a, Vector3 b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

// Compute gravitational force vector acting on object due to Earth
Vector3 gravitational_force(SpaceObject obj) {
    Vector3 force;
    float r = distance(obj.position, earth_pos);
    
    // Calculate the magnitude of the gravitational force (magnitude meaning size / strength)
    //               = "size / length"
    float F_mag = (G * M * obj.mass) / (r * r);
    
    // Normalize the position vector to get direction
    // by dividing the vector by its own length
    Vector3 r_hat = {
        (obj.position.x - earth_pos.x) / r,
        (obj.position.y - earth_pos.y) / r,
        (obj.position.z - earth_pos.z) / r
    };
    
    // Calculate force components
    force.x = -F_mag * r_hat.x;
    force.y = -F_mag * r_hat.y;
    force.z = -F_mag * r_hat.z;

    return force;
}

// Update position and velocity of the space object
void update_space_object(SpaceObject *obj) {
    // Compute gravitational force acting on the object
    Vector3 force = gravitational_force(*obj);
    
    // Compute acceleration (F = ma)
    Vector3 acceleration = {
        force.x / obj->mass,
        force.y / obj->mass,
        force.z / obj->mass
    };
    
    // Update velocity (v = v + a * dt) formelsamling s.44
    obj->velocity.x += acceleration.x * DELTA_T;
    obj->velocity.y += acceleration.y * DELTA_T;
    obj->velocity.z += acceleration.z * DELTA_T;
    
    // Update position (x = x + v * dt) formelsamling s.44
    obj->position.x += obj->velocity.x * DELTA_T;
    obj->position.y += obj->velocity.y * DELTA_T;
    obj->position.z += obj->velocity.z * DELTA_T;
}

int space_generate() {
    
    SpaceObject debris;
    debris.position = (Vector3){0, 0, 1000000};
    debris.velocity = (Vector3){7000, 7000, 0};
    debris.mass = 40;  // 20 kg

    for (int i = 0; i < 20000; i++) {
        SpaceObject temp_space_object = {(Vector3){0, 0, 1000000}, (Vector3){rand() % 7000, rand() % 7000, rand() % 7000}, 0.5};
        space_objects[i] = temp_space_object;
    }

    // Simulate for a certain number of steps
    for (int step = 1; step < 1000; step++) {
        for (int i = 0; i < 20000; i++) {
            update_space_object(&space_objects[i]);
        
            printf("Step %d: Position = (%f, %f, %f) Velocity = (%f, %f, %f)\n", step,
               space_objects[i].position.x, space_objects[i].position.y, space_objects[i].position.z,
               space_objects[i].velocity.x, space_objects[i].velocity.y, space_objects[i].velocity.z);
        }
        sleep(1);
        
    }    

    return 0;
}




/*   UPDATE   */

int space_tick() {

    return 0;
}

