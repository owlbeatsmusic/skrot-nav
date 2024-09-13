#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "awlib_log/log.h"

int main() {

	awlib_log_create("log.txt");
	printf("[SKROT-NAV - 2024]\n");
	
	renderer_initialize();
	renderer_render_screen();

	int nav_status = nav_create();
	if (nav_status != 0) printf("%s skrot-nav ran into an error (code=%d))\n", RENDERER_ERROR_PRINT, nav_status);

	int space_status = space_start();
	if (space_status != 0) printf("%s space simulation ran into an error (code=%d))\n", RENDERER_ERROR_PRINT, space_status);

	return 0;
}