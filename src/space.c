#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "global.h"



/*   VARIABLES   */

const float G =  6.67e-11;
const float M = 5.977e24;
const float DELTA_T = 0.01;
const float EARTH_RADIUS = 6371000;

Vector3 earth_pos = {0, 0, 0};

int spaceobject_ammount = 100;
const int MAX_SPACEOBJECTS = 24576;
SpaceObject spaceobjects[MAX_SPACEOBJECTS];

// create spaceobject at first available index in spaceobjects[]
// returns index of object
int space_append_spaceobject(SpaceObjectType type, Vector3 position, Vector3 velocity, float mass) {
    int empty_index = 0;
    int i = 0;
    while (spaceobjects[i].mass != 0) {
        if (i >= MAX_SPACEOBJECTS) return -1;
        i++;
    }
    empty_index = i;
    SpaceObject temp_space_object = {
        type,
        (Vector3){
            position.x, 
            position.y, 
            position.z},
        (Vector3){
            velocity.x,  //random_direction[2]*sqrt(G * M / (1+random_direction[2])), 
            velocity.y,  //sqrt(G * M / (1+orbit_radius_xyz[1])),  //random_direction[0]*sqrt(G * M / (1+random_direction[0])), 
            velocity.z} ,//sqrt(G * M / (1+orbit_radius_xyz[0]))}, //random_direction[1]*sqrt(G * M / (1+random_direction[1]))}, 
        mass
    };
    spaceobjects[empty_index] = temp_space_object;
    return empty_index;
}




/*   CALCULATIONS    */

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




/*      CORE FUNCTIONS      */

int space_start() {

    srand(time(NULL));

    // generate space debris
    for (int i = 0; i < spaceobject_ammount; i++) {
        float orbit_radius_xyz_base[] = {
            (rand() % (int)EARTH_RADIUS) - EARTH_RADIUS/2, 
            (rand() % (int)EARTH_RADIUS) - EARTH_RADIUS/2,
            (rand() % (int)EARTH_RADIUS) - EARTH_RADIUS/2
        };
        float orbit_radius_xyz[3];

        // create random postions in x, y and z. Normalize and 
        // multiply by earth radius for point around sphere(earth)
        for (int i = 0; i < 3; i++) {
            orbit_radius_xyz[i] = orbit_radius_xyz_base[i] * (1/sqrt(pow(orbit_radius_xyz_base[0], 2) + pow(orbit_radius_xyz_base[1], 2) + pow(orbit_radius_xyz_base[2], 2))) * (EARTH_RADIUS + 100000);
            printf("xyz=%f\n", orbit_radius_xyz_base[i]);
        }


        space_append_spaceobject(DEBRIS, (Vector3){orbit_radius_xyz[0], orbit_radius_xyz[1], orbit_radius_xyz[2]}, (Vector3){0, 0, 0}, 0.5);
        /*SpaceObject temp_space_object = {
            DEBRIS,
            (Vector3){
                orbit_radius_xyz[0], 
                orbit_radius_xyz[1], 
                orbit_radius_xyz[2]},                   // TODO : random runt hela jorden skrot med rätt hastighet - hjälp.
            (Vector3){
                0,  //random_direction[2]*sqrt(G * M / (1+random_direction[2])), 
                0,//,sqrt(G * M / (1+orbit_radius_xyz[1])),  //random_direction[0]*sqrt(G * M / (1+random_direction[0])), 
                0},//sqrt(G * M / (1+orbit_radius_xyz[0]))}, //random_direction[1]*sqrt(G * M / (1+random_direction[1]))}, 
            0.5};*/
    }


    // create xz view
    renderer_draw_orbitview(0, 0, RENDERER_SCREEN_WIDTH/2, RENDERER_SCREEN_HEIGHT, 'x', 'z');

    // create xy view
    renderer_draw_orbitview(RENDERER_SCREEN_WIDTH / 2, 0, RENDERER_SCREEN_WIDTH/2, RENDERER_SCREEN_HEIGHT, 'x', 'y');


    // Simulate for a certain number of steps
    int steps = 10000000;
    for (int step = 1; step < steps; step++) {

        // update views each X ammount of steps
        if (step % 1000 == 1) {
            renderer_render_screen(); 
            printf("time passed=%fs\n", step * DELTA_T);
        }

        // update all space objects positions
        for (int i = 0; i < spaceobject_ammount; i++) {

            update_space_object(&spaceobjects[i]);
         
            // xz view
            renderer_set_pixel(
                renderer_convert_to_screen_coord(spaceobjects[i].position.x, RENDERER_SCREEN_WIDTH / 4), 
                renderer_convert_to_screen_coord(spaceobjects[i].position.z, RENDERER_SCREEN_HEIGHT / 2)
            );

            // xy view
            renderer_set_pixel(
                renderer_convert_to_screen_coord(spaceobjects[i].position.x, 3*RENDERER_SCREEN_WIDTH / 4), 
                renderer_convert_to_screen_coord(spaceobjects[i].position.y, RENDERER_SCREEN_HEIGHT / 2)
            );
        }
    }          
    
    renderer_render_screen(); 
    
    return 0;
}



