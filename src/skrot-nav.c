#include <stdio.h>
#include "global.h"

/*

ENERGY:
https://en.wikipedia.org/wiki/Solar_panels_on_spacecraft



*/


int nav_spaceobjects_index = 0;


// OBJECTS / NAVIGATION

void nav_update_tracked_objects_internal(int spaceobjects_index) {

    return;
}

SpaceObject nav_identify_object_internal(RadarObject radar_obj) {
    SpaceObject spaceobject;
    return spaceobject;
}

void nav_set_destination_internal(Vector3 target) {

    return;
}



// PHSICAL CALCULATIONS

int nav_check_for_collisions_internal(SpaceObject *robot) {

    return 0;
}

Vector3 nav_predict_future_position_internal(SpaceObject obj, float time) {
    Vector3 v3;
    return v3;
}


// CORE

int nav_update() {

    return 0;
}

int nav_create() {
    nav_spaceobjects_index = space_append_spaceobject(SPACECRAFT, (Vector3){0, 0, EARTH_RADIUS + 1200000}, (Vector3){8000, 0, 0}, 20);
    if (nav_spaceobjects_index == -1) return -1;

    // define devices
    RadarDevice radar1 = {{{1, 1, 1}}, 180, 1, 180, 5};

    // ( ENERGY (BATTERY) )

    // PROCESS INFORTMATION FROM SENSORS

    // PROPULSION SYSTEM 

    // BACKUP PROTOCOL

    // COMMUNICATION

    return 0;
}