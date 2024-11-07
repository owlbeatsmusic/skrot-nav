// This code is for the CDS (command and data subsystem)

#include <stdio.h>
#include "../global.h"

/*
GENERAL:
https://science.nasa.gov/learn/basics-of-space-flight/chapter13-1/


ENERGY:
https://en.wikipedia.org/wiki/Solar_panels_on_spacecraft
*/


typedef struct {
    FILE *file;
} SpacecraftEvent;
SpacecraftEvent spacecraft_sequence_of_events[1024];

typedef enum {
    COMMAND,
    NAVIGATION,
    TELEMETRY
    // TODO: add more
} DataPacketType;

typedef struct { 
    DataPacketType data_packet_type;
    u_int32_t packet_timestamp;            // time of packet creation  
    u_int32_t meassurement_timestamp;      // time of eg. angle observation
    u_int16_t packet_id;            // unique for all packets
    u_int16_t source_id;            // from which system / subsystem (/device)
    u_int16_t data_length;     
    u_int16_t sequence_number;      // if multiple packets, which order
    char general_data[512];

    // COMMAND
    FILE *SEF_file;             // SEquence of Events

    // NAVIGATION
    int observation_latitude;
    int observation_longitude;
    int observation_altitude;
    u_int32_t distance; 
    int radial_velocity;        // from/towards earth
    int azimuth_angle;          // on earth sky
    int elevation_angle;        // on earth sky

} CommunicationDataPacket;



u_int32_t sclk = 0; // clock

float current_delta_velocity;
Vector3 last_mathematical_position;   
Vector3 last_observed_position; 


/*       OTHER: DEVICE INTERACTION      */

int nav_run_telemetry_analysis(void) { // create HealthData

    // check all devices, create healthdata reports and save and continue if error occoured or any critical levels.


    return 0;
}

int nav_anomalie_found_protocol(HealthData health_data) { // from CDS(this) or other FP(fault protection) algorithms or downlink
    
    // eg. termniate device processes

    return 0;
}

int nav_enter_safing(void) {

    // types:
    // - simple; baseline safing instructions read from ROM
    // - complex; in CDS RAM, can be updated

    return 0;
}

// TODO : implement CLT (https://science.nasa.gov/learn/basics-of-space-flight/chapter11-1/)


void nav_energy_lowpower_protocol_internal(void) {
    
    return;
}


int nav_communication_assemble_packet(void) {

    // eg. compression

    return 0;
}

int nav_communication_store_packet(CommunicationDataPacket *comm_data_packet) {

    return 0;
}

int nav_communication_send_packet(CommunicationDataPacket *comm_data_packet) { // send to transmitter

    return 0;
}





/*       NASA 1&3: FLIGHT PATH CONTROL      */

int nav_evaluate_drift_from_course(void) {

    return 0;
}

int calculate_course_delta_velocity(void) {

    return 0;
}

int nav_communication_command_from_downlink(CommunicationDataPacket comm_data_packet) {

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


// COMMUNICATION

int nav_communication_receive_spacecraft_event_file(FILE *SEF_file) {

    return 0;
}

int nav_communication_send_view_period_file(FILE *view_period_file) {

    return 0;
}




/*       NASA 2: SPACECRAFT POSITION      */

int nav_update_orbit_previous_path(void) {

    return 0;
}

int nav_evaluate_current_position(void) { // begin the Batch Filter

    return 0;
}


int nav_communication_receive_velocity(float distance) {

    return 0;
}

int nav_communication_receive_distance_from_earth(Vector3 velocity) {

    return 0;
}



int nav_check_for_collisions_internal(SpaceObject *robot) {

    return 0;
}

Vector3 nav_predict_future_position_internal(SpaceObject obj, float time) {
    Vector3 v3 = {0, 0, 0};
    return v3;
}







/*       OTHER: CONNECTION TO SIMULATION      */

int nav_spaceobjects_index = 0;

int nav_update(void) {

    return 0;
}

int nav_create(void) {
    nav_spaceobjects_index = space_append_spaceobject(SPACECRAFT, (Vector3){0, 0, EARTH_RADIUS + 1200000}, (Vector3){8000, 0, 0}, 20);
    if (nav_spaceobjects_index == -1) return -1;



    return 0;
}
