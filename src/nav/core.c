#include<unistd.h>
#include <stdint.h>
#include <time.h>

#include "common/bool.h"
#include "nav/core.h"
#include "nav/communication.h"
#include "nav/flight_path.h"
#include "awlib_log/log.h"

typedef struct {
    FILE *file;
} SpacecraftEvent;

int nav_spaceobjects_index = 0;

SpacecraftEvent spacecraft_sequence_of_events[1024];
uint32_t start_time = 0; // for setting sclk
uint32_t sclk = 0; // clock

Bool system_active = TRUE;

/* Aka. Get time */
int nav_get_sclk(void) {
    sclk = (uint32_t)time(NULL) - start_time;
    return sclk;
}

void nav_shutdown(void) {

    // safetly shutdown all systems

    awlib_log_t("log/log.txt", "nav shutdown successfully\n");
}

/* The main loop for the whole navigation. */
int nav_proc_main_internal(void) {
    awlib_log_t("log/log.txt", "main nav-process started\n");

    while (system_active) {
        printf("t=%d\n", nav_get_sclk());
        
        // test:
        FlightPath fp;
        nav_create_flight_path(&fp);

        system_active = FALSE;
    }

    nav_shutdown();
    return 0;
}

/* Initialize and add "spacecraft" as a object in simulated space. */
int nav_create(void) {
    //nav_spaceobjects_index = space_append_spaceobject(SPACECRAFT, (Vector3){0, 0, EARTH_RADIUS + 1200000}, (Vector3){8000, 0, 0}, 20);
    //if (nav_spaceobjects_index == -1) return -1;

    start_time = time(NULL);

    nav_proc_main_internal();
    return 0;
}
