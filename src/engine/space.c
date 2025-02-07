/*
    SPACE.C

    This file handles the space simulation. The main objective is 
    to simulate the movement of everything in orbit around the earth.

    (description updated: 2025-02-07)
*/


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "engine/space.h"
#include "engine/renderer.h"
#include "common/vector.h"
#include "nav/core.h"

 

/*   VARIABLES   */

const float G =  6.67e-11;
const float M = 5.977e24;
const float DELTA_T = 0.01;
const float EARTH_RADIUS = 6371000;

Vector3 earth_pos = {0, 0, 0};

int spaceobject_amount = 100;
const int MAX_SPACEOBJECTS = 34000;
SpaceObject spaceobjects[MAX_SPACEOBJECTS];


/*   CALCULATIONS    */


// create spaceobject at first available index in spaceobjects[]
// returns index of object
int space_append_spaceobject(SpaceObjectType type, Vector3 position, Vector3 velocity, float mass) {
    int empty_index = 0;
    int i = 0;
    while (spaceobjects[i].mass != 0) { // TODO: does not comply with LOC-2 
        if (i >= MAX_SPACEOBJECTS) return -1;
        i++;
    }

    // calculate orbital velocity
    int r = vector_distance(position, earth_pos);
    float orbital_velocity = sqrt(G * M / r);

    // calculate velocity direction
    Vector3 temp_vector = {0, 0, 1}; 
    Vector3 velocity_direction = vector_cross_product(position, temp_vector);
    velocity_direction = vector_normalize(velocity_direction);

    empty_index = i;
    SpaceObject temp_space_object = {
        type,
        (Vector3){
            position.x, 
            position.y, 
            position.z},
        (Vector3){
            velocity_direction.x * orbital_velocity,  //random_direction[2]*sqrt(G * M / (1+random_direction[2])), 
            velocity_direction.y * orbital_velocity,   //sqrt(G * M / (1+orbit_radius_xyz[1])),  //random_direction[0]*sqrt(G * M / (1+random_direction[0])), 
            velocity_direction.z * orbital_velocity} , //sqrt(G * M / (1+orbit_radius_xyz[0]))}, //random_direction[1]*sqrt(G * M / (1+random_direction[1]))}, 
        mass
    };
    spaceobjects[empty_index] = temp_space_object;
    return empty_index;
}


// Compute gravitational force vector acting on object due to Earth
Vector3 gravitational_force_internal(SpaceObject obj) {
    Vector3 force;

    // size of force
    float r = vector_distance(obj.position, earth_pos);
    float F_mag = (G * M * obj.mass) / (r * r);
    
    // direction of force
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

// update position and velocity of the space object
void update_space_object_internal(SpaceObject *obj) {
    Vector3 force = gravitational_force_internal(*obj);
    
    // (F = ma)
    Vector3 acceleration = {
        force.x / obj->mass,
        force.y / obj->mass,
        force.z / obj->mass
    };


    // Update position (s = s + v * dt)
    // DE: s(t + dt) = s(t) + s'(t) * dt  
    obj->position.x += obj->velocity.x * DELTA_T;
    obj->position.y += obj->velocity.y * DELTA_T;
    obj->position.z += obj->velocity.z * DELTA_T;

    // Update velocity (v = v + a * dt)
    // DE: s'(t + dt) = s'(t) + s''(t) * dt
    obj->velocity.x += acceleration.x * DELTA_T;
    obj->velocity.y += acceleration.y * DELTA_T;
    obj->velocity.z += acceleration.z * DELTA_T;

}




/*      CORE FUNCTIONS      */

int space_start(void) {

    srand(time(NULL));

    // generate space debris
    for (int i = 0; i < spaceobject_amount; i++) {
        float orbit_radius_xyz_base[] = {
            (rand() % (int)EARTH_RADIUS) - EARTH_RADIUS/2, 
            (rand() % (int)EARTH_RADIUS) - EARTH_RADIUS/2,
            (rand() % (int)EARTH_RADIUS) - EARTH_RADIUS/2
        };
        float orbit_radius_xyz[3];

        // create random positions in x, y and z. Normalize and 
        // multiply by earth radius for point around sphere(earth)
        for (int i = 0; i < 3; i++) {
            orbit_radius_xyz[i] = orbit_radius_xyz_base[i] * (1/sqrt(pow(orbit_radius_xyz_base[0], 2) + pow(orbit_radius_xyz_base[1], 2) + pow(orbit_radius_xyz_base[2], 2))) * (EARTH_RADIUS + 700000 + rand() % 1000000);
        }

        space_append_spaceobject(DEBRIS, (Vector3){orbit_radius_xyz[0], orbit_radius_xyz[1], orbit_radius_xyz[2]}, (Vector3){0, 0, 0}, 0.5);
    }

    renderer_render_all_views();

    // simulate for a certain number of steps
    int steps = 3000000;
    for (int step = 0; step < steps; step++) {


        // update views each X amount of steps
        if ((step) % 5000 == 1) {
            renderer_render_screen(); 
            renderer_initialize();

            renderer_render_all_views();

            printf("time passed: %ds   (%fmin)   (%fh)\n", (int)(step * DELTA_T), (step * DELTA_T)/60, (step * DELTA_T)/3600);
            printf("step: %d / %d\n", step, steps);
            printf("\nSPACECRAFT:\n   Position = (%f, %f, %f) \n   Velocity = (%f, %f, %f)\n",
               spaceobjects[nav_spaceobjects_index].position.x, spaceobjects[nav_spaceobjects_index].position.y, spaceobjects[nav_spaceobjects_index].position.z,
               spaceobjects[nav_spaceobjects_index].velocity.x, spaceobjects[nav_spaceobjects_index].velocity.y, spaceobjects[nav_spaceobjects_index].velocity.z);
            nav_core_proc_main_tick();

        }
        
        

        for (int i = 0; i < spaceobject_amount; i++) {

            // update spaceobject's positions
            update_space_object_internal(&spaceobjects[i]);

  
            // update screen information
	        for (int j = 0; j < 3; j++) {
                int pos_x = 0;
                int pos_y = 0;
                int offset_x = spaceobjects[renderer_views[j].center_object_index].position.x;
                int offset_y = spaceobjects[renderer_views[j].center_object_index].position.y;
                switch (renderer_views[j].x_axis_symbol) {
                    case 'x':
                        pos_x = spaceobjects[i].position.x;
                        offset_x = spaceobjects[renderer_views[j].center_object_index].position.x;
                        break;
                    case 'y':
                        pos_x = spaceobjects[i].position.y;
                        offset_x = spaceobjects[renderer_views[j].center_object_index].position.y;
                        break;
                    case 'z':
                        pos_x = spaceobjects[i].position.z;
                        offset_x = spaceobjects[renderer_views[j].center_object_index].position.z;
                }
                switch (renderer_views[j].y_axis_symbol) {
                    case 'x':
                        pos_y = spaceobjects[i].position.x;
                        offset_y = spaceobjects[renderer_views[j].center_object_index].position.x;
                        break;
                    case 'y':
                        pos_y = spaceobjects[i].position.y;
                        offset_y = spaceobjects[renderer_views[j].center_object_index].position.y;
                        break;
                    case 'z':
                        pos_y = spaceobjects[i].position.z;
                        offset_y = spaceobjects[renderer_views[j].center_object_index].position.z;
                }

                if (renderer_views[j].center_object_index == -1) {
                    offset_x = 0;
                    offset_y = 0;
                }

                int screen_x = (int)(((pos_x-offset_x) / (float)renderer_views[j].scale) * RENDERER_ORBIT_VIEW_WIDTH) + RENDERER_ORBIT_VIEW_WIDTH  / 2 + renderer_views[j].view_x * RENDERER_ORBIT_VIEW_WIDTH;
                int screen_y = (int)(((pos_y-offset_y) / (float)renderer_views[j].scale) * RENDERER_ORBIT_VIEW_WIDTH) + RENDERER_ORBIT_VIEW_HEIGHT / 2 + renderer_views[j].view_y * RENDERER_ORBIT_VIEW_HEIGHT;
                
                if (screen_x >= (1 + renderer_views[j].view_x) * RENDERER_ORBIT_VIEW_WIDTH
                    | screen_x <= (renderer_views[j].view_x) * RENDERER_ORBIT_VIEW_WIDTH
                    | screen_y >= (1 + renderer_views[j].view_x) * RENDERER_ORBIT_VIEW_WIDTH
                    //| screen_y <= (renderer_views[j].view_x) * RENDERER_ORBIT_VIEW_WIDTH
                    ) continue;
                
                renderer_set_pixel(screen_x, screen_y, renderer_spaceobject_type_color[spaceobjects[i].type].symbol, (char*)renderer_spaceobject_type_color[spaceobjects[i].type].fg_color, (char*)renderer_spaceobject_type_color[spaceobjects[i].type].bg_color);
            }
            
            /*
            int spacecraft_screen_xz_x = (int)(((spaceobjects[i].position.x-spaceobjects[nav_spaceobjects_index].position.x) / (float)1000000) * RENDERER_ORBIT_VIEW_WIDTH) + RENDERER_ORBIT_VIEW_WIDTH / 2;
            int spacecraft_screen_xz_y = (int)(((spaceobjects[i].position.z-spaceobjects[nav_spaceobjects_index].position.z) / (float)10000000) * RENDERER_ORBIT_VIEW_WIDTH) + RENDERER_ORBIT_VIEW_WIDTH / 2;

            int screen_xz_x = renderer_convert_to_screen_coord(spaceobjects[i].position.x, RENDERER_ORBIT_VIEW_WIDTH + RENDERER_ORBIT_VIEW_WIDTH / 2); 
            int screen_xz_y = renderer_convert_to_screen_coord(spaceobjects[i].position.z, RENDERER_ORBIT_VIEW_HEIGHT / 2); 

            int screen_xy_x = renderer_convert_to_screen_coord(spaceobjects[i].position.x, RENDERER_ORBIT_VIEW_WIDTH + 3*RENDERER_ORBIT_VIEW_WIDTH / 2);
            int screen_xy_y = renderer_convert_to_screen_coord(spaceobjects[i].position.y, RENDERER_ORBIT_VIEW_HEIGHT / 2); 

            if (spaceobjects[i].type == SPACECRAFT) {
                renderer_set_pixel(spacecraft_screen_xz_x, spacecraft_screen_xz_y, 'o', "\x1b[33m", "\x1b[41m");
                renderer_set_pixel(screen_xz_x, screen_xz_y, 'o', "\x1b[33m", "\x1b[41m");
                renderer_set_pixel(screen_xy_x, screen_xy_y, 'o', "\x1b[33m", "\x1b[41m");
            }
            else {
                renderer_set_pixel(spacecraft_screen_xz_x, spacecraft_screen_xz_y, '*', "\x1b[35m", "\x1b[47m");
                renderer_set_pixel(screen_xz_x, screen_xz_y, '*', "\x1b[35m", "\x1b[47m");
                renderer_set_pixel(screen_xy_x, screen_xy_y, '*', "\x1b[35m", "\x1b[47m");
            }
            */
        }

        /*
        if ((step) % 10 == 0) {
            nav_core_proc_main_tick();
            printf("time passed: %ds   (%fmin)   (%fh)\n", (int)(step * DELTA_T), (step * DELTA_T)/60, (step * DELTA_T)/3600);
        }
        */

       usleep(10);
    }          
    
    renderer_render_screen(); 
    
    return 0;
}
