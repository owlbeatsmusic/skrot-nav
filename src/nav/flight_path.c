/*
    FLIGHT_PATH.C

    This file handles the navigation of the spacecraft (path, drift, maneuvers, object detection). 
    It is the centerpoint for the navigation system; getting information from "position.c". 

    (description updated: 2025-01-12)
*/


#include <stdio.h>
#include <stdint.h>

#include "nav/core.h"
#include "nav/flight_path.h"
#include "nav/devices.h"
#include "nav/communication.h"
#include "nav/position.h"
#include "engine/space.h"


float current_delta_velocity;

Vector3 tracked_objects[200];


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

RadarDevice radar = {
    .d = {
        .id = 0,
        .offset = {0, 0, 0},
        .powered_on = TRUE,
        .mass = 0.2
    },
    .min_range = 0,
    .max_range = 10000,
    .azimuth_step_size = 10,
    .elevation_step_size = 10,
    .from_azimuth_angle = 0,
    .to_azimuth_angle = 180,
    .from_elevation_angle = 0,
    .to_elevation_angle = 180,
    .devices_radar_frequency_band = 0.1,
    .radarModulationType = CW
};

void update_tracked_objects_internal(void) {

    // TODO: this is just for testing purposes as we don't have the actual data
    int k = 0;
    for (int i = 0; i < MAX_SPACEOBJECTS; i++) {
        double dist = vector_distance(spaceobjects[nav_spaceobjects_index].position, spaceobjects[i].position);
        if (dist < 10000 && i != nav_spaceobjects_index) {
            if (k == 200) break;
            printf("); Detected object at (%.2f, %.2f, %.2f), distance: %.2f\n", 
                   spaceobjects[i].position.x, spaceobjects[i].position.y, spaceobjects[i].position.z, dist);
            tracked_objects[k] = spaceobjects[i].position;
            k++;
        }
    }

    //devices_radar_scan(&radar);

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

    position_evaluate_current_position();
    update_tracked_objects_internal();

    return 0;
}
