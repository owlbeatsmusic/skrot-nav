#include <stdio.h>
#include "global.h"

/*
GENERAL:
https://science.nasa.gov/learn/basics-of-space-flight/chapter13-1/


ENERGY:
https://en.wikipedia.org/wiki/Solar_panels_on_spacecraft
*/


// This code is for the CDS (command and data subsystem)



// GENERAL VARIABLES

unsigned int sclk = 0; // clock



/*       OTHER: DEVICE INTERACTION      */

typedef struct {
    // eg. CCSDS (https://public.ccsds.org/implementations/missions.aspx)
} DataPacket;

typedef struct {
    // eg. switch positions, subsystem states, voltages, temperatures, pressures.
} HealthData;


// ANALYSIS

int nav_run_telemetry_analysis() { // create HealthData

    return 0;
}

int nav_anomalie_found_protocol(HealthData health_data) { // from CDS(this) or other FP(fault protection) algorithms or downlink
    
    // eg. termniate device processes

    return 0;
}


// ENERGY (power)

void nav_energy_lowpower_protocol_internal() {
    
    return;
}


// COMMUNICATION

int nav_communication_assemble_packet() {

    // eg. compression

    return 0;
}

int nav_communication_store_packet(DataPacket *data_packet) {

    return 0;
}

int nav_communication_send_packet(DataPacket *data_packet) { // send to transmitter

    return 0;
}





/*       NASA 1&3: FLIGHT PATH CONTROL      */

int current_delta_velocity;
Vector3 last_mathematical_position;   
Vector3 last_observed_position; 

typedef struct {
    FILE *file;
} SpacecraftEvent;
SpacecraftEvent spacecraft_sequence_of_events[1024];

int nav_evaluate_drift_from_course() {

    return 0;
}

int calculate_course_delta_velocity() {

    return 0;
}

int nav_communication_command_from_downlink() {

    return 0;
}



// PROPULSION SYSTEM

void nav_propulsion_set_destination_internal(Vector3 target) {

    return;
}



// OBJECTS

void nav_update_tracked_objects_internal(int spaceobjects_index) {

    return;
}

SpaceObject nav_identify_object_internal(RadarObject radar_obj) {
    SpaceObject spaceobject;
    return spaceobject;
}


// COMMUNICATION

int nav_communication_receive_spacecraft_event_file(FILE *SEF_file) {

    return 0;
}

int nav_communication_send_view_period_file(FILE *view_period_file) {

    return 0;
}







/*       NASA 2: ACTUAL SPACECRAFT POSITION      */

int nav_update_orbit_previous_path() {

    return 0;
}

int nav_evaluate_current_position() { // begin the Batch Filter

    return 0;
}



// COMMUNICATION

//int nav_communication_receive_information();

int nav_communication_receive_velocity(float distance) {

    return 0;
}

int nav_communication_receive_distance_from_earth(Vector3 velocity) {

    return 0;
}



// PHSICAL CALCULATIONS

int nav_check_for_collisions_internal(SpaceObject *robot) {

    return 0;
}

Vector3 nav_predict_future_position_internal(SpaceObject obj, float time) {
    Vector3 v3;
    return v3;
}







/*       OTHER: CONNECTION TO SIMULATION      */

int nav_spaceobjects_index = 0;

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