#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "nav/devices.h"
#include "nav/communication.h"
#include "common/print.h"
#include "common/id.h"


char *data_packet_type_label[] = {
    "COMMAND",
    "NAVIGATION",
    "TELEMETRY",

    "DEBRIS_STATUS",
    "HEALTH_STATUS",
    "DATA_REQUEST"
};

int nav_communication_parse_event_file(FILE *SEF_file) {

    return 0;
}

int nav_communication_send_view_period_file(FILE *view_period_file) {

    return 0;
}

// initializes a new communication data packet depending on what packet type is specified. 
void nav_communication_create_data_packet(CommunicationDataPacket *comm_data_packet, DataPacketType data_packet_type) {

    // create & set id
    comm_data_packet->packet_timestamp = (unsigned int) time(NULL);
    comm_data_packet->data_packet_type = data_packet_type;
    id_generate(comm_data_packet->packet_id, 1); // "1" for spacecraft
    // eg. compression

    return;
}

int nav_communication_store_packet(CommunicationDataPacket *comm_data_packet) {

    // TODO: write to file

    return 0;
}

int nav_communication_send_packet(CommunicationDataPacket *comm_data_packet) { // send to transmitter

    printf("PACKET SENDING... : %s\n| time=%u\n| packet_id=%s\n", data_packet_type_label[comm_data_packet->data_packet_type], (unsigned int)comm_data_packet->packet_timestamp, comm_data_packet->packet_id);
    printf("\n");

    int send_status = devices_transmittor_send_communication_packet(comm_data_packet);
    if (send_status == -1) {
        printf("%s failed to send packet through transmittor (code=%d))\n", PRINT_ERROR, send_status);
    }

    return 0;
}

int nav_communication_receive_packet(CommunicationDataPacket comm_data_packet) { // from transmitter

    printf("PACKET RECEIVED : %s\n| time=%u\n| packet_id=%s\n| request_id=%s\n", data_packet_type_label[comm_data_packet.data_packet_type], (unsigned int)comm_data_packet.packet_timestamp, comm_data_packet.packet_id, comm_data_packet.request_id);
    printf("\n");

    switch (comm_data_packet.data_packet_type) {
        case COMMAND:
            nav_communication_parse_event_file(comm_data_packet.SEF_file);
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

    return 0;
}


