/*
    FLIGHT_PATH.C

    This file handles the navigation of the spacecraft (path, drift, maneuvers, object detection). 
    It is the centerpoint for the navigation system; getting information from "position.c". 

    (description updated: 2025-01-12)
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

void flightpath_drift_status(HealthData *health_data) {
    
}

int evaluate_drift_from_course_internal(void) {

    return 0;
}

int calculate_course_delta_velocity_internal(void) {

    return 0;
}



/* ----------- */
/*   Objects   */
/* ----------- */

void update_tracked_objects_internal(int spaceobjects_index) {

    return;
}

SpaceObject flightpath_identify_object_internal(RadarObject radar_obj) {
    SpaceObject spaceobject = {DEBRIS, {0, 0, 0}, {0, 0, 0}, 1, 0.2};
    return spaceobject;
}



/* ----------- */
/*   Maneuver  */
/* ----------- */

int flightpath_create_course_maneuver(FlightPathManeuver *maneuver) {
    // 1. get self current position
    // 2. run devices
    // 3. identify objects
    // 4. 
    return 0;
}

void flightpath_perform_maneuver(FlightPathManeuver *maneuver) {
    
}



/* ----------- */
/*    Path     */
/* ----------- */

int flightpath_update_path(FlightPath *flight_path) {

    return 0;
}

int flightpath_create_path(FlightPath *flight_path) {

    // test:
    position_evaluate_current_position();

    return 0;
}
