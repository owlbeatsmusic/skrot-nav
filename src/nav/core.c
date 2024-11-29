#include "nav/core.h"
#include "nav/communication.h"

typedef struct {
    FILE *file;
} SpacecraftEvent;

u_int32_t sclk = 0; // clock

SpacecraftEvent spacecraft_sequence_of_events[1024];

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
