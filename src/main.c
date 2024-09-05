#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "awlib_log/log.h"

int main() {
	
	awlib_log_create("log.txt");

	printf("[SKROT-NAV - 2024]\n");
	renderer_initialize();
	renderer_render_screen();
	printf("[space]\n");
	space_start();
	return 0;
}