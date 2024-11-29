#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "engine/renderer.h"
#include "engine/space.h"
#include "common/print.h"
#include "nav/core.h"

int main(void) {

	srand(time(NULL));

	printf("[SKROT-NAV - 2024]\n"); 
	
	//renderer_initialize();
	//renderer_render_screen();

	int nav_status = nav_create();
	if (nav_status != 0) printf("%s skrot-nav ran into an error (code=%d))\n", PRINT_ERROR, nav_status);

	//renderer_views[0].center_object_index = nav_spaceobjects_index;

	//int space_status = space_start();
	//if (space_status != 0) printf("%s space simulation ran into an error (code=%d))\n", PRINT_ERROR, space_status);

	
	return 0;
}

