#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "awlib_log/log.h"

/*   VARIABLES   */

const float G =  6.67e-11;
const float M = 5.977e24;
const float DELTA_T = 0.001;
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
void update_space_object(SpaceObject *obj) {
    // Compute gravitational force acting on the object
    Vector3 force = gravitational_force(*obj);
    
    // (F = ma)
    Vector3 acceleration = {
        force.x / obj->mass,
        force.y / obj->mass,
        force.z / obj->mass
    };      

    obj->position.x += obj->velocity.x * DELTA_T;
    obj->position.y += obj->velocity.y * DELTA_T;
    obj->position.z += obj->velocity.z * DELTA_T;

    // Update velocity (v = v + a * dt) formelsamling s.44
    obj->velocity.x += acceleration.x * DELTA_T;
    obj->velocity.y += acceleration.y * DELTA_T;
    obj->velocity.z += acceleration.z * DELTA_T;

}

int space_start() {

    // exmaple object    
    float orbital_radius = EARTH_RADIUS + 1000000;
    SpaceObject debris;
    debris.position = (Vector3){0, 100000, orbital_radius};
    debris.velocity = (Vector3){sqrt(G * M / orbital_radius), -1000, 0};
    debris.mass = 10;  // 20 kg

    /* for (int i = 0; i < 1000; i++) {
        SpaceObject temp_space_object = {(Vector3){0, 0, 1000000}, (Vector3){rand() % 7000, rand() % 7000, rand() % 7000}, 0.5};
        space_objects[i] = temp_space_object;
    } */

    //renderer_set_pixel(earth_pos.x + GLOBAL_SCREEN_WIDTH / 4, earth_pos.z +  + GLOBAL_SCREEN_HEIGHT / 2);
    //renderer_set_pixel(earth_pos.x + 3 * GLOBAL_SCREEN_WIDTH / 4, earth_pos.z +  + GLOBAL_SCREEN_HEIGHT / 2);
    
    //xz visual
    int earth_radius = (int)((6371000 / (float)20000000) * GLOBAL_SCREEN_WIDTH/2);
    renderer_draw_circle(GLOBAL_SCREEN_WIDTH / 4, GLOBAL_SCREEN_HEIGHT / 2, earth_radius);
    renderer_draw_line_vertical(1, 1, GLOBAL_SCREEN_HEIGHT-2);
    renderer_draw_text("z", 2, 1);
    renderer_draw_line_horizontal(2, GLOBAL_SCREEN_HEIGHT-2, GLOBAL_SCREEN_WIDTH/2-4);
    renderer_draw_text("x", GLOBAL_SCREEN_WIDTH/2-5, GLOBAL_SCREEN_HEIGHT-3);

    //xy visual
    renderer_draw_circle(1 + 3*GLOBAL_SCREEN_WIDTH / 4, GLOBAL_SCREEN_HEIGHT / 2, earth_radius);
    renderer_draw_line_vertical(GLOBAL_SCREEN_WIDTH/2+1, 1, GLOBAL_SCREEN_HEIGHT-2);
    renderer_draw_text("y", GLOBAL_SCREEN_WIDTH/2+2, 1);
    renderer_draw_line_horizontal(GLOBAL_SCREEN_WIDTH/2+2, GLOBAL_SCREEN_HEIGHT-2, GLOBAL_SCREEN_WIDTH-4);
    renderer_draw_text("x", GLOBAL_SCREEN_WIDTH-5, GLOBAL_SCREEN_HEIGHT-3);


    // Simulate for a certain number of steps
    int steps = 1000000000;
    for (int step = 1; step < steps; step++) {

        // update
        update_space_object(&debris);
        if (step % 10000000 == 1) {
            renderer_render_screen();
            printf("time passed=%fh\n", step * DELTA_T / 3600);
        }

        // render
        int xz_renderer_x = (int)((debris.position.x / (float)20000000) * GLOBAL_SCREEN_WIDTH/2) + GLOBAL_SCREEN_WIDTH / 4;
        int xz_renderer_y = (int)((debris.position.z / (float)20000000) * GLOBAL_SCREEN_HEIGHT) + GLOBAL_SCREEN_HEIGHT / 2;
        renderer_set_pixel(xz_renderer_x, xz_renderer_y);

        int xy_renderer_x = 1 + (int)((debris.position.x / (float)20000000) * GLOBAL_SCREEN_WIDTH/2) + 3*GLOBAL_SCREEN_WIDTH / 4;
        int xy_renderer_y = (int)((debris.position.y / (float)20000000) * GLOBAL_SCREEN_HEIGHT) + GLOBAL_SCREEN_HEIGHT / 2;
        renderer_set_pixel(xy_renderer_x, xy_renderer_y);

        //printf("x=%d, y=%d\n", renderer_x, renderer_y);
        //printf("Step %d: Position = (%f, %f, %f) Velocity = (%f, %f, %f)\n", step,
            //debris.position.x, debris.position.y, debris.position.z,
            //debris.velocity.x, debris.velocity.y, debris.velocity.z);
        /*for (int i = 0; i < 20000; i++) {
            update_space_object(&space_objects[i]);
            //printf("Step %d: Position = (%f, %f, %f) Velocity = (%f, %f, %f)\n", step,
            //   space_objects[i].position.x, space_objects[i].position.y, space_objects[i].position.z,
            //   space_objects[i].velocity.x, space_objects[i].velocity.y, space_objects[i].velocity.z);
        }*/
        
    }          
    renderer_render_screen(); 
    


    return 0;
}




/*   UPDATE   */

int space_tick() {

    return 0;
}

