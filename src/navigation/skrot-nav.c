// This code is for the CDS (command and data subsystem)

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char *data_packet_type_label[] = {
    "COMMAND",
    "NAVIGATION",
    "TELEMETRY",

    "DEBRIS_STATUS",
    "HEALTH_STATUS"
};

u_int32_t sclk = 0; // clock

SpacecraftEvent spacecraft_sequence_of_events[1024];

float current_delta_velocity;
Vector3 last_mathematical_position;   
Vector3 last_observed_position; 




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

int nav_communication_parse_event_file(FILE *SEF_file) {

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


// initializes a new communication data packet depending on what packet type is specified. 
void nav_communication_create_data_packet(CommunicationDataPacket *comm_data_packet, DataPacketType data_packet_type) {

    comm_data_packet->packet_timestamp = (unsigned int) time(NULL);
    sprintf(comm_data_packet->packet_id, "%08X%04X", (unsigned int)time(NULL), rand() * 0xFFFF);
    comm_data_packet->data_packet_type = data_packet_type;
    
    // eg. compression

    return;
}

int nav_communication_store_packet(CommunicationDataPacket *comm_data_packet) {

    // TODO: write to file

    return 0;
}

int nav_communication_send_packet(CommunicationDataPacket *comm_data_packet) { // send to transmitter

    int send_status = devices_transmittor_send_communication_packet(*comm_data_packet);
    if (send_status == -1) {
        printf("%s failed to send packet through transmittor (code=%d))\n", RENDERER_ERROR_PRINT, send_status);
    }
    return 0;
}

int nav_communication_receive_packet(CommunicationDataPacket *comm_data_packet) { // from transmitter

    printf("PACKET RECEIVED : %s\n| time=%u\n| packet_id=%s\n", data_packet_type_label[comm_data_packet->data_packet_type], (unsigned int)comm_data_packet->packet_timestamp, comm_data_packet->packet_id);

    switch (comm_data_packet->data_packet_type) {
        case COMMAND:
            nav_communication_parse_event_file(comm_data_packet->SEF_file);
            break;

        case NAVIGATION:
            break;

        case TELEMETRY:
            break;

        case DEBRIS_STATUS:
            break;

        case HEALTH_STATUS:
            break;
    }

    return 0;
}




/*       OTHER: CONNECTION TO SIMULATION      */

int nav_spaceobjects_index = 0;

int nav_update(void) {

    return 0;
}

int nav_create(void) {
    //nav_spaceobjects_index = space_append_spaceobject(SPACECRAFT, (Vector3){0, 0, EARTH_RADIUS + 1200000}, (Vector3){8000, 0, 0}, 20);
    //if (nav_spaceobjects_index == -1) return -1;

    CommunicationDataPacket comm_data_packet;
    nav_communication_create_data_packet(&comm_data_packet, COMMAND);
    nav_communication_send_packet(&comm_data_packet);

    return 0;
}
