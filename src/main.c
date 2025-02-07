/*
	MAIN.C

	The objective of this file is to initialize everything (log, nav, ...) 
	and start the engine (space & renderer simulations).

	(description updated: 2025-01-12)
*/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "awlib_log/log.h"
#include "engine/renderer.h"
#include "engine/space.h"
#include "common/print.h"
#include "nav/core.h"

int main(void) {
	srand(time(NULL));

	awlib_log_create("log/log.txt");
	awlib_log_t("log/log.txt", "log file created\n");	
	
	renderer_initialize();
	awlib_log_t("log/log.txt", "renderer_initialzed\n");
	renderer_render_screen();


	// initialize navigation system
	int nav_status = nav_core_create();
	if (nav_status != 0) {
		awlib_log_t("log/log.txt", "skrot-nav ran into an error (code=%d)\n", nav_status);
	    printf("%s skrot-nav ran into an error (code=%d)\n", PRINT_ERROR, nav_status);
	}
	renderer_views[0].center_object_index = nav_spaceobjects_index;

	// start space simulation
	int space_status = space_start();
	if (space_status != 0) printf("%s space simulation ran into an error (code=%d))\n", PRINT_ERROR, space_status);

	return 0;
}

