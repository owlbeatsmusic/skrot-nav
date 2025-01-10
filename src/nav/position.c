/*
    POSITION.C

    This file handles the spacecrafts position. The main objective is to evaluate the 
    position in space using the three measurements we can get from earth (NASA: chapter13-1).
        Additionally this file handles collision checking and predicting future position.
    
    (description updated: 2025-01-10)
*/

#include "engine/space.h"
#include "common/vector.h"

#include "nav/communication.h"


Vector3 last_mathematical_position;   
Vector3 last_observed_position; 


int nav_communication_get_distance_from_earth(Vector3 *velocity) {
    
    CommunicationDataPacket data_packet;
    data_packet.request_earth_distance = TRUE;

    nav_communication_create_data_packet(&data_packet, DATA_REQUEST);
    nav_communication_send_packet(&data_packet);
    
    return 0;
}

int nav_communication_get_radial_velocity(float *distance) {

    CommunicationDataPacket data_packet;
    data_packet.request_radial_velocity = TRUE;

    nav_communication_create_data_packet(&data_packet, DATA_REQUEST);
    nav_communication_send_packet(&data_packet);

    return 0;
}

int nav_communication_get_earth_sky_angles(float *azimuth_angle, float *elevation_angle) {

    CommunicationDataPacket data_packet;
    data_packet.request_earth_sky_angles = TRUE;

    nav_communication_create_data_packet(&data_packet, DATA_REQUEST);
    nav_communication_send_packet(&data_packet);

    return 0;
}



int nav_evaluate_current_position(void) { // begin the Batch Filter
    
    return 0;
}

int nav_check_for_collisions_internal(SpaceObject *robot) {

    return 0;
}


/* Can also be self. */
Vector3 nav_predict_future_position_internal(SpaceObject obj, float delta_time) {
    Vector3 v3 = {0, 0, 0};
    return v3;
}
