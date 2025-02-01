/*
    POSITION.C

    This file handles the spacecrafts position. The main objective is to evaluate the 
    position in space using the three measurements we can get from earth (NASA: chapter13-1).
        Additionally this file handles collision checking and predicting future position.
    
    (description updated: 2025-01-10)
*/

#include <stdint.h>
#include <string.h>

#include "engine/space.h"
#include "common/vector.h"
#include "common/print.h"
#include "common/bool.h"
#include "nav/communication.h"

#include "awlib_log/log.h"


Vector3 last_mathematical_position;   
Vector3 last_observed_position; 

Bool waiting_for_earth_distance = FALSE;
uint32_t last_earth_distance = 0;

Bool waiting_for_radial_velocity = FALSE;
int last_radial_velocity = 0;

Bool waiting_for_earth_sky_angles = FALSE;
float last_earth_sky_azimuth = 0;
float last_earth_sky_elevation = 0;


// Set the last observed distance from earth to the distance
// provided in the response packet.
void position_update_distance_from_earth(CommunicationDataPacket *comm_data_packet) {

    communication_request_queue_remove(comm_data_packet->request_id);

    waiting_for_earth_distance = FALSE;
    last_earth_distance = comm_data_packet->distance;
    printf("%sdistance from earth: %d\n", PRINT_DEBUG, last_earth_distance);
}

// Create and send a communication data packet to downlink and
// add the request id to queue.
void position_request_distance_from_earth(void) {

    waiting_for_earth_distance = TRUE;
    
    CommunicationDataPacket data_packet;
    data_packet.request_earth_distance = TRUE;

    communication_create_data_packet(&data_packet, DATA_REQUEST);
    communication_request_queue_add(data_packet.packet_id, &position_update_distance_from_earth);
    communication_send_packet(&data_packet);

    
}


// Set the last observed radial velocity to the velocity
// provided in the response packet.
void position_update_radial_velocity(CommunicationDataPacket *comm_data_packet) {
    
    communication_request_queue_remove(comm_data_packet->request_id);

    waiting_for_radial_velocity = FALSE;
    last_radial_velocity = comm_data_packet->radial_velocity;

    printf("%sradial velocity from earth: %d\n", PRINT_DEBUG, last_radial_velocity);
}

// Create and send a communication data packet to downlink and
// add the request id to queue.
void position_request_radial_velocity(void) {

    CommunicationDataPacket data_packet;
    data_packet.request_radial_velocity = TRUE;

    communication_create_data_packet(&data_packet, DATA_REQUEST);
    communication_request_queue_add(data_packet.packet_id, &position_update_radial_velocity);
    communication_send_packet(&data_packet);
}


// Set the last observed angles on the earth sky to the angles
// provided in the response packet.
void position_update_earth_sky_angles(CommunicationDataPacket *comm_data_packet) {

    communication_request_queue_remove(comm_data_packet->request_id);

    waiting_for_earth_sky_angles = FALSE;
    last_earth_sky_azimuth = comm_data_packet->azimuth_angle;
    last_earth_sky_elevation = comm_data_packet->elevation_angle;

    printf("%sangles on earth sky from earth: (%f; %f)\n", PRINT_DEBUG, last_earth_sky_azimuth, last_earth_sky_elevation);
}

// Create and send a communication data packet to downlink and
// add the request id to queue.
void position_request_earth_sky_angles(void) {

    CommunicationDataPacket data_packet;
    data_packet.request_earth_sky_angles = TRUE;

    communication_create_data_packet(&data_packet, DATA_REQUEST);
    communication_request_queue_add(data_packet.packet_id, &position_update_earth_sky_angles);
    communication_send_packet(&data_packet);

}



int position_evaluate_current_position(void) { // begin the Batch Filter

    // test:
    position_request_distance_from_earth();
    position_request_radial_velocity();
    position_request_earth_sky_angles();

    return 0;
}

int position_check_for_collisions_internal(SpaceObject *robot) {

    return 0;
}


/* Can also be self. */
Vector3 position_predict_future_position_internal(SpaceObject obj, float delta_time) {
    Vector3 v3 = {0, 0, 0};
    return v3;
}
