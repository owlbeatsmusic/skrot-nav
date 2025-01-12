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
#include "nav/communication.h"


Vector3 last_mathematical_position;   
Vector3 last_observed_position; 

uint32_t last_earth_distance = 0;

// Set the last observed distance from earth to the distance
// provided in the response packet.
int position_update_distance_from_earth(CommunicationDataPacket *comm_data_packet) {
    printf("%sdistance=%u\n", PRINT_DEBUG, comm_data_packet->distance);
    return 0;
}

// Create and send a communication data packet to downlink and
// add the request id to queue.
int position_request_distance_from_earth(uint32_t *distance) {
    
    CommunicationDataPacket data_packet;
    data_packet.request_earth_distance = TRUE;

    communication_create_data_packet(&data_packet, DATA_REQUEST);
    communication_request_queue_add(data_packet.packet_id, &position_update_distance_from_earth);
    communication_send_packet(&data_packet);
    
    return 0;
}


int position_request_radial_velocity(Vector3 *velocity) {

    CommunicationDataPacket data_packet;
    data_packet.request_radial_velocity = TRUE;

    communication_create_data_packet(&data_packet, DATA_REQUEST);
    communication_send_packet(&data_packet);

    return 0;
}

int position_request_earth_sky_angles(float *azimuth_angle, float *elevation_angle) {

    CommunicationDataPacket data_packet;
    data_packet.request_earth_sky_angles = TRUE;

    communication_create_data_packet(&data_packet, DATA_REQUEST);
    communication_send_packet(&data_packet);

    return 0;
}



int position_evaluate_current_position(void) { // begin the Batch Filter

    // test:
    uint32_t earth_dist = 0;
    position_request_distance_from_earth(&earth_dist);

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
