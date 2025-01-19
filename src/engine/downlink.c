/* 
    DOWNLINK.C

    This file handles the simulation / emulation of the downlink. This is needed for
    demonstration of the navigation system.

    (description updated: 2025-01-10)
*/

#include <string.h>
#include <time.h>

#include "nav/communication.h"
#include "nav/core.h"
#include "engine/downlink.h"
#include "engine/space.h"
#include "common/id.h"
#include "common/print.h"
#include "common/vector.h"

#include "awlib_log/log.h"


void downlink_create_communication_data_packet_internal(CommunicationDataPacket *new_data_packet, DataPacketType data_packet_type) {

    // create & set id
    new_data_packet->packet_timestamp = (unsigned int) time(NULL); // TODO: fixa för time(null) e irrelevelant, integrera med sclck
    new_data_packet->data_packet_type = data_packet_type;
    id_generate(new_data_packet->packet_id, 0); // "0" for downlink
    // eg. compression

    return;
}

int downlink_send_communication_data_packet(CommunicationDataPacket new_data_packet) {

    printf("%s downlink sent packet.\n\n", PRINT_DEBUG);

    communication_receive_packet(new_data_packet);

    return 0;
}


int downlink_receive_communication_data_packet(CommunicationDataPacket received_comm_data_packet) {

    printf("%s downlink received packet.\n", PRINT_DEBUG);

    CommunicationDataPacket new_data_packet;

    switch (received_comm_data_packet.data_packet_type) {
        case COMMAND:
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
            strcpy(new_data_packet.request_id, received_comm_data_packet.packet_id);

            if (received_comm_data_packet.request_earth_distance == TRUE) {
                //new_data_packet.distance = vector_distance(spaceobjects[nav_spaceobjects_index].position, earth_pos) - EARTH_RADIUS;
                awlib_log_t("log/log.txt", "\nSPACECRAFT:\n   Position = (%f, %f, %f)\n",
                    spaceobjects[nav_spaceobjects_index].position.x, spaceobjects[nav_spaceobjects_index].position.y, spaceobjects[nav_spaceobjects_index].position.z);
                //awlib_log_t("log/log.txt","%s spacecraft position: %d\n", PRINT_DEBUG, spaceobjects[nav_spaceobjects_index].position.y);
                new_data_packet.distance = vector_distance(spaceobjects[nav_spaceobjects_index].position, earth_pos) - EARTH_RADIUS;

            }

            downlink_create_communication_data_packet_internal(&new_data_packet, TELEMETRY);
            downlink_send_communication_data_packet(new_data_packet);

            break;
    }

    return 0;
}
