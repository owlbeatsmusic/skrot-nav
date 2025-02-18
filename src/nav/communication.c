/*
    COMMUNICATION.C

    This file handles communication.
    additionally between subsystems within the navigation system.

    (description updated: 2025-02-18)
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "nav/devices.h"
#include "nav/communication.h"
#include "common/print.h"
#include "common/id.h"
#include "awlib_log/log.h"


char *data_packet_type_label[] = {
    "COMMAND",
    "NAVIGATION",
    "TELEMETRY",

    "DEBRIS_STATUS",
    "HEALTH_STATUS",
    "DATA_REQUEST"
};

// Search for first free index to create queue pair
int communication_request_queue_add(char request_id[], void (*function_pointer)(CommunicationDataPacket *)) {
    for (int i = 0; i < 64; i ++) {
        if (communication_request_queue[i].function_pointer == NULL) {
            communication_request_queue[i].function_pointer = function_pointer;
            strcpy(communication_request_queue[i].request_id, request_id);
            break;
        }
    }
    return 0;
}

// Search for index of request id and clear it from request queue
int communication_request_queue_remove(char request_id[]) {
    Bool found_id = FALSE;
    for (int i = 0; i < 64; i ++) {
        if (strcmp(communication_request_queue[i].request_id, request_id) == 0) {
            strcpy(communication_request_queue[i].request_id, "");
            communication_request_queue[i].function_pointer = NULL;
            found_id = TRUE;
            break;
        }
    }
    if (found_id == FALSE) printf("%srequest_id not found in request queue.\n", PRINT_WARNING);
    return 0;
}

int communication_parse_event_file(FILE *SEF_file) {

    return 0;
}

int communication_send_view_period_file(FILE *view_period_file) {

    return 0;
}

// initializes a new communication data packet depending on what packet type is specified. 
void communication_create_data_packet(CommunicationDataPacket *comm_data_packet, DataPacketType data_packet_type) {

    // create & set id
    comm_data_packet->packet_timestamp = (unsigned int) time(NULL);
    comm_data_packet->data_packet_type = data_packet_type;
    id_generate(comm_data_packet->packet_id, 1); // "1" for spacecraft
    // eg. compression

    return;
}

int communication_store_packet(CommunicationDataPacket *comm_data_packet) {

    // TODO: write to file

    return 0;
}

int communication_send_packet(CommunicationDataPacket *comm_data_packet) { // send to transmitter

    //printf("PACKET SENDING... : %s\n| time=%u\n| packet_id=%s\n\n", data_packet_type_label[comm_data_packet->data_packet_type], (unsigned int)comm_data_packet->packet_timestamp, comm_data_packet->packet_id);
    int send_status = devices_transmitter_send_communication_packet(comm_data_packet);
    if (send_status == -1) {
        printf("%s failed to send packet through transmitter (code=%d))\n", PRINT_ERROR, send_status);
    }

    return 0;
}

int communication_receive_packet(CommunicationDataPacket comm_data_packet) { 

    //printf("PACKET RECEIVED : %s\n| time=%u\n| packet_id=%s\n| request_id=%s\n", data_packet_type_label[comm_data_packet.data_packet_type], (unsigned int)comm_data_packet.packet_timestamp, comm_data_packet.packet_id, comm_data_packet.request_id);
    //printf("\n");

    switch (comm_data_packet.data_packet_type) {
        case COMMAND:
            communication_parse_event_file(comm_data_packet.SEF_file);
            break;

        case NAVIGATION:
            break;

        case TELEMETRY:
            break;

        case DEBRIS_STATUS:
            break;

        case HEALTH_STATUS:
            break;

        case DATA_REQUEST:
            break;
    }

    // If there is a request id then call the function associated with
    // the id of the request pack. The packet is a then a response packet.
    if ((int)strlen(comm_data_packet.request_id) != 0) {
        for (int i = 0; i < 64; i++) {
            if (strcmp(comm_data_packet.request_id, communication_request_queue[i].request_id) == 0) {
                communication_request_queue[i].function_pointer(&comm_data_packet);
                break;
            }
        }
    }

    return 0;
}


