#include <stdio.h>
#include <string.h>
#include "global.h"

const char COLORCODE_DEFAULT[]    = "\x1b[m";
const char COLORCODE_FG_BLACK[]   = "\x1b[30m";
const char COLORCODE_BG_BLACK[]   = "\x1b[40m";
const char COLORCODE_FG_RED[]     = "\x1b[31m";
const char COLORCODE_BG_RED[]     = "\x1b[41m";
const char COLORCODE_FG_GREEN[]   = "\x1b[32m";
const char COLORCODE_BG_GREEN[]   = "\x1b[42m";
const char COLORCODE_FG_YELLOW[]  = "\x1b[33m";
const char COLORCODE_BG_YELLOW[]  = "\x1b[43m";
const char COLORCODE_FG_BLUE[]    = "\x1b[34m";
const char COLORCODE_BG_BLUE[]    = "\x1b[44m";
const char COLORCODE_FG_MAGENTA[] = "\x1b[35m";
const char COLORCODE_BG_MAGENTA[] = "\x1b[45m";
const char COLORCODE_FG_CYAN[]    = "\x1b[36m";
const char COLORCODE_BG_CYAN[]    = "\x1b[46m";
const char COLORCODE_FG_WHITE[]   = "\x1b[37m";
const char COLORCODE_BG_WHITE[]   = "\x1b[47m";

extern const int GLOBAL_SCREEN_WIDTH  = 100;
extern const int GLOBAL_SCREEN_HEIGHT = 50;

typedef struct {
	char symbol;
	char fg_color[8];
	char bg_color[8];
	int id;
} ScreenPixel;

ScreenPixel renderer_screengrid[GLOBAL_SCREEN_HEIGHT][GLOBAL_SCREEN_WIDTH];

void renderer_set_pixel(int x, int y) {
    ScreenPixel temp_pixel = {'#', "\x1b[37m", "\x1b[45m"};
    renderer_screengrid[y][x] = temp_pixel;
}

void renderer_set_pixel_earth(int x, int y) {
    ScreenPixel temp_pixel = {'#', "\x1b[32m", "\x1b[46m"};
    renderer_screengrid[y][x] = temp_pixel;
}

/* Much faster and does not require iteration */
void renderer_terminalclear_internal() {
	printf("\033[H\033[J");
}

/* Just places cursor, use printf after this function */
void renderer_gotoxy_internal(int x, int y) {
	printf("\033[%d;%dH", y, x);
}

// TODO: vad fan gör den här funktionen här egentligen?
void renderer_fullstrcpy(char dest[], const char source[], int dest_arry_size) {
	for (int i = 0; i < dest_arry_size; i++) {
		dest[i] = source[i];
	}
}

void renderer_screenclear_internal() {
	for (int y = 0; y < GLOBAL_SCREEN_HEIGHT; y++) {
		for (int x = 0; x < GLOBAL_SCREEN_WIDTH; x++) {
			renderer_screengrid[y][x].symbol = ' ';
			renderer_fullstrcpy(renderer_screengrid[y][x].fg_color, COLORCODE_FG_WHITE, sizeof(renderer_screengrid[y][x].fg_color));
			renderer_fullstrcpy(renderer_screengrid[y][x].bg_color, COLORCODE_BG_BLACK, sizeof(renderer_screengrid[y][x].fg_color));
		}
	}
}

int renderer_render_screen() {
	renderer_terminalclear_internal();
	
	for (int y = 0; y < GLOBAL_SCREEN_HEIGHT; y++) {
		for (int x = 0; x < GLOBAL_SCREEN_WIDTH; x++) {	
			printf("%s%s%c", renderer_screengrid[y][x].fg_color, renderer_screengrid[y][x].bg_color, renderer_screengrid[y][x].symbol);
		}
		printf("\n");
	}
	printf("%s", COLORCODE_DEFAULT);	

    return 0;
}

void renderer_initialize() {
	renderer_screenclear_internal();
	renderer_render_screen();
    printf("%s", COLORCODE_DEFAULT);
}