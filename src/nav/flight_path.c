/*
    FLIGHT_PATH.C

    This file handles the navigation of the spacecraft. It is the centerpoint
    for the navigation system; getting information from "position.c".

    (updated last: 2025-01-10)
*/


#include <stdio.h>
#include <stdint.h>

#include "nav/flight_path.h"
#include "nav/communication.h"
#include "nav/position.h"
#include "engine/space.h"


float current_delta_velocity;


/* ----------- */
/*    Drift    */
/* ----------- */

void nav_drift_status(HealthData *health_data) {
    
}

int nav_evaluate_drift_from_course_internal(void) {

    return 0;
}

int nav_calculate_course_delta_velocity_internal(void) {

    return 0;
}



/* ----------- */
/*   Objects   */
/* ----------- */

void nav_update_tracked_objects_internal(int spaceobjects_index) {

    return;
}

SpaceObject nav_identify_object_internal(RadarObject radar_obj) {
    SpaceObject spaceobject = {DEBRIS, {0, 0, 0}, {0, 0, 0}, 1, 0.2};
    return spaceobject;
}



/* ----------- */
/*   Manouver  */
/* ----------- */

int nav_create_course_manouver(FlightPathManouver *manouver) {
    // 1. get self current position
    // 2. run devices
    // 3. identify objects
    // 4. 
    return 0;
}

void nav_perform_manouver(FlightPathManouver *manouver) {
    
}



/* ----------- */
/*    Path     */
/* ----------- */

int nav_update_flight_path(FlightPath *flight_path) {

    return 0;
}

int nav_create_flight_path(FlightPath *flight_path) {
    
    // test:
    nav_evaluate_current_position();

    return 0;
}
