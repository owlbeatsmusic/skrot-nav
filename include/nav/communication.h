#ifndef COMMUNCATION_H_
#define COMMUNCATION_H_

#include <stdio.h>
#include <stdlib.h>

#include "common/bool.h"
#include "nav/devices_types.h"

typedef struct {

    uint16_t packet_timestamp;            // time of packet creation  
    uint16_t meassurement_timestamp;      // time of eg. angle observation
    char packet_id[18];                    // unique for all packets
    char source_id[18];                    // from which system / subsystem (/device)
    Device *device;

    /* device */
    uint8_t communication_status;  // 0=offline, 1=online, 2=degraded

    uint16_t battery_level;    
    uint8_t battery_status;        // 0 = normal, 1 = warning, 2 = critical)

    float temperature; 
    uint8_t thermal_status;        // 0 = normal, 1 = warning, 2 = critical)

    float fuel_level;             
    uint8_t fuel_status;           // 0 = normal, 1 = warning, 2 = critical)

    float pressure;      
    uint8_t pressure_status;       // 0 = normal, 1 = warning, 2 = critical)

    uint16_t radiation;        
    uint8_t radiation_level;       // 0 = normal, 1 = warning, 2 = critical)

    uint8_t error_code;            // if not 0, error has occoured in device / substystem
    uint16_t uptime;    

    /* TODO: "subsystems" */ 
    uint32_t drift_status;        // 0 = normal, 1 = warning, 2 = critical)

} HealthData;

typedef enum {

    // RECEIVE
    COMMAND,
    NAVIGATION,
    TELEMETRY,
    
    // SEND
    DEBRIS_STATUS,
    HEALTH_STATUS, 
    DATA_REQUEST

    // TODO: add more
} DataPacketType;

extern char *data_packet_type_label[];

typedef struct { 
    DataPacketType data_packet_type;
    
    uint16_t packet_timestamp;            // time of packet creation  
    uint16_t meassurement_timestamp;      // time of eg. angle observation
    char packet_id[18];            // unique for all packets
    char source_id[18];            // from which system / subsystem (/device)
    char request_id[18];           // id of request-packet sent to downlink
    uint16_t data_length;     
    uint16_t sequence_number;      // if multiple packets, which order
    char general_data[256];

    // HEALTH
    HealthData health_data;

    // COMMAND
    FILE *SEF_file;             // SEquence of Events

    // NAVIGATION
    /*int observation_latitude;
    int observation_longitude;
    int observation_altitude; */
    
    Bool request_earth_distance;
    uint32_t distance; 
    
    Bool request_radial_velocity;
    int radial_velocity;        // from/towards earth

    Bool request_earth_sky_angles;
    int azimuth_angle;          // on earth sky
    int elevation_angle;        // on earth sky

} CommunicationDataPacket;


typedef struct {
    char request_id[18];
    int (*function_pointer)(CommunicationDataPacket *);
} RequestQueuePair;

RequestQueuePair communication_request_queue[64];

extern int communication_request_queue_add(char request_id[], int (*function_pointer)(CommunicationDataPacket *));
extern int communication_request_queue_remove(char request_id[]);

extern int communication_parse_event_file(FILE *SEF_file);
extern int communication_send_view_period_file(FILE *view_period_file);

extern void communication_create_data_packet(CommunicationDataPacket *comm_data_packet, DataPacketType data_packet_type);
extern int communication_store_packet(CommunicationDataPacket *comm_data_packet);
extern int communication_send_packet(CommunicationDataPacket *comm_data_packet); // send to transmitter
extern int communication_receive_packet(CommunicationDataPacket comm_data_packet); // from transmitter


#endif
