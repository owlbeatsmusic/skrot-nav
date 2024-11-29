#ifndef COMMUNCATION_H_
#define COMMUNCATION_H_

#include <stdio.h>
#include <stdlib.h>

#include "nav/devices_types.h"

typedef struct {

    Device *device;

    u_int8_t communication_status;  // 0=offline, 1=online, 2=degraded

    u_int16_t battery_level;    
    u_int8_t battery_status;        // 0 = normal, 1 = warning, 2 = critical)

    float temperature; 
    u_int8_t thermal_status;        // 0 = normal, 1 = warning, 2 = critical)

    float fuel_level;             
    u_int8_t fuel_status;           // 0 = normal, 1 = warning, 2 = critical)

    float pressure;      
    u_int8_t pressure_status;       // 0 = normal, 1 = warning, 2 = critical)

    u_int16_t radiation;        
    u_int8_t radiation_level;       // 0 = normal, 1 = warning, 2 = critical)

    u_int8_t error_code;            // if not 0, error has occoured in device / substystem
    u_int32_t uptime;               

} HealthData;

typedef enum {

    // RECEIVE
    COMMAND,
    NAVIGATION,
    TELEMETRY,
    
    // SEND
    DEBRIS_STATUS,
    HEALTH_STATUS 

    // TODO: add more
} DataPacketType;

extern char *data_packet_type_label[];

typedef struct { 
    DataPacketType data_packet_type;
    
    u_int32_t packet_timestamp;            // time of packet creation  
    u_int32_t meassurement_timestamp;      // time of eg. angle observation
    char packet_id[17];            // unique for all packets
    char source_id[17];            // from which system / subsystem (/device)
    u_int16_t data_length;     
    u_int16_t sequence_number;      // if multiple packets, which order
    char general_data[256];

    // HEALTH
    HealthData health_data;

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



extern int nav_communication_parse_event_file(FILE *SEF_file);
extern int nav_communication_send_view_period_file(FILE *view_period_file);

extern void nav_communication_create_data_packet(CommunicationDataPacket *comm_data_packet, DataPacketType data_packet_type);
extern int nav_communication_store_packet(CommunicationDataPacket *comm_data_packet);
extern int nav_communication_send_packet(CommunicationDataPacket *comm_data_packet); // send to transmitter
extern int nav_communication_receive_packet(CommunicationDataPacket *comm_data_packet); // from transmitter


#endif
