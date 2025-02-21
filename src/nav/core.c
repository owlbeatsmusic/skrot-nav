/*
    CORE.C

    This file is the starting point of the system and contains the
    main loop. The main objective for this file is to handle the
    non-navigation parts of the system.

    (description updated 2025-01-25)
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
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
int nav_core_get_sclk(void) {
    sclk = (uint32_t)time(NULL) - start_time;
    return sclk;
}

void nav_core_shutdown(void) {

    // safetly shutdown all systems

    awlib_log_t("log/log.txt", "nav shutdown successfully\n");
}

/* nav_core_proc_main_tick */
void nav_core_proc_main_tick(void) {

    // test:
    FlightPath fp;
    flightpath_create_path(&fp);

    


}

/* The main loop for the whole navigation. */
int nav_core_proc_main_internal(void) {
    awlib_log_t("log/log.txt", "main nav-process started\n");

    while (system_active) {

        nav_core_proc_main_tick(); 

        // TODO: in actual implementation this is a loop but now 'tick' is called from space loop
        
        system_active = FALSE;
    }

    nav_core_shutdown();
    return 0;
}

/* Initialize and add "spacecraft" as a object in simulated space. */
int nav_core_create(void) {

    nav_spaceobjects_index = space_append_spaceobject(SPACECRAFT, (Vector3){0, EARTH_RADIUS + 400000, 0}, (Vector3){8000, 0, 0}, 20);
    if (nav_spaceobjects_index == -1) return -1;


    start_time = time(NULL);
    nav_core_proc_main_internal();

    return 0;
}
