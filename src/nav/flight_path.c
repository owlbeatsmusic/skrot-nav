#include <stdio.h>

#include "nav/communication.h"
#include "engine/space.h"

float current_delta_velocity;

int nav_evaluate_drift_from_course(void) {

    return 0;
}

int calculate_course_delta_velocity(void) {

    return 0;
}


void nav_propulsion_set_destination_internal(Vector3 target) {

    return;
}


void nav_update_tracked_objects_internal(int spaceobjects_index) {

    return;
}

SpaceObject nav_identify_object_internal(RadarObject radar_obj) {
    SpaceObject spaceobject = {DEBRIS, {0, 0, 0}, {0, 0, 0}, 1, 0.2};
    return spaceobject;
}
