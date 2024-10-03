#include <stdio.h>
#include "global.h"

/*

ENERGY:
https://en.wikipedia.org/wiki/Solar_panels_on_spacecraft



*/

int nav_spaceobjects_index = 0;

void nav_update_tracked_objects(SpaceObject tracked_objects[], int num_objects);

Vector3 nav_predict_future_position(SpaceObject obj, float time) {

}
void nav_set_destination(Vector3 target) {


}
int nav_check_for_collisions(SpaceObject *robot, SpaceObject tracked_objects[], int num_objects) {

}


int nav_update() {

    return 0;
}


int nav_create() {
    nav_spaceobjects_index = space_append_spaceobject(SPACECRAFT, (Vector3){0, 0, EARTH_RADIUS + 1200000}, (Vector3){8000, 0, 0}, 20);
    if (nav_spaceobjects_index == -1) return -1;

    // define devices
    RadarDevice radar1 = {{1, 1, 1}, 180, 1, 180, 5};

    // ( ENERGY (BATTERY) )

    // PROCESS INFORTMATION FROM SENSORS

    // PROPULSION SYSTEM 

    // BACKUP PROTOCOL

    // COMMUNICATION

    return 0;
}