#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "global.h"
//#include "awlib_log/log.h"

/*   VARIABLES   */

const float G =  6.67e-11;
const float M = 5.977e24;
const float DELTA_T = 0.01;
const float EARTH_RADIUS = 6371000;

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

int space_object_ammount = 2000;
SpaceObject space_objects[24576];





/*   SPACE    */

// Compute distance between two points in 3D space
float distance(Vector3 a, Vector3 b) {
    return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
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
// eulers method
void update_space_object(SpaceObject *obj) {
    // Compute gravitational force acting on the object
    Vector3 force = gravitational_force(*obj);
    
    // (F = ma)
    Vector3 acceleration = {
        force.x / obj->mass,
        force.y / obj->mass,
        force.z / obj->mass
    };


    // Update postition (s = s + v * dt) formelsamling s.44
    // DE: s(t + dt) = s(t) + s'(t) * dt  
    obj->position.x += obj->velocity.x * DELTA_T;
    obj->position.y += obj->velocity.y * DELTA_T;
    obj->position.z += obj->velocity.z * DELTA_T;

    // Update velocity (v = v + a * dt) formelsamling s.44
    // DE: s'(t + dt) = s'(t) + s''(t) * dt
    obj->velocity.x += acceleration.x * DELTA_T;
    obj->velocity.y += acceleration.y * DELTA_T;
    obj->velocity.z += acceleration.z * DELTA_T;

}

int space_start() {

    // generate space debris
    for (int i = 0; i < space_object_ammount; i++) {
        int orbit_radius_x = 0;
        int orbit_radius_y = 0;
        int orbit_radius_z = 0;
        SpaceObject temp_space_object = {
            (Vector3){
                orbit_radius_x, 
                orbit_radius_y, 
                orbit_radius_z},                   // TODO : random runt hela jorden skrot med rätt hastighet - hjälp.
            (Vector3){
                0, //random_direction[2]*sqrt(G * M / (1+random_direction[2])), 
                0, //random_direction[0]*sqrt(G * M / (1+random_direction[0])), 
                0},//random_direction[1]*sqrt(G * M / (1+random_direction[1]))}, 
            0.5};
        space_objects[i] = temp_space_object;
    }

    //xz view
    renderer_draw_orbitview(0, 0, GLOBAL_SCREEN_WIDTH/2, GLOBAL_SCREEN_HEIGHT, 'x', 'z');

    //xy view
    renderer_draw_orbitview(GLOBAL_SCREEN_WIDTH / 2, 0, GLOBAL_SCREEN_WIDTH/2, GLOBAL_SCREEN_HEIGHT, 'x', 'y');

    // Simulate for a certain number of steps
    int steps = 100000;
    for (int step = 1; step < steps; step++) {

        // update views each X ammount of steps
        if (step % 1000 == 1) {
            renderer_render_screen(); 
            printf("time passed=%fh\n", step * DELTA_T / 3600);
        }

        // update all space objects positions
        for (int i = 0; i < space_object_ammount; i++) {

            update_space_object(&space_objects[i]);
         
            // xz view
            renderer_set_pixel(
                renderer_convert_to_screen_coord(space_objects[i].position.x, GLOBAL_SCREEN_WIDTH / 4), 
                renderer_convert_to_screen_coord(space_objects[i].position.z, GLOBAL_SCREEN_HEIGHT / 2)
            );

            // xz view
            renderer_set_pixel(
                renderer_convert_to_screen_coord(space_objects[i].position.x, 3*GLOBAL_SCREEN_WIDTH / 4), 
                renderer_convert_to_screen_coord(space_objects[i].position.y, GLOBAL_SCREEN_HEIGHT / 2)
            );
        }

        
    }          
    renderer_render_screen(); 
    


    return 0;
}
