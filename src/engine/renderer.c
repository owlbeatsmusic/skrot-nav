#include <stdio.h>
#include <string.h>
#include "engine/renderer.h"

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

const int RENDERER_SCREEN_WIDTH  = 150;
const int RENDERER_SCREEN_HEIGHT = 50;

const int RENDERER_ORBIT_VIEW_WIDTH = 50;
const int RENDERER_ORBIT_VIEW_HEIGHT = 50;

const int RENDERER_SPACE_WIDTH = 20000000;

ScreenPixel renderer_screengrid[RENDERER_SCREEN_HEIGHT][RENDERER_SCREEN_WIDTH];

View renderer_views[] = {
	{0, 0, -1, RENDERER_SPACE_WIDTH/2, 'x', 'z'}, // 5000000
	{1, 0, -1, RENDERER_SPACE_WIDTH,   'x', 'z'},
	{2, 0, -1, RENDERER_SPACE_WIDTH,   'x', 'y'},
};

const ScreenPixel renderer_spaceobject_type_color[] = {
	{'*', "\x1b[35m", "\x1b[47m"}, // DEBRIS
	{'o', "\x1b[33m", "\x1b[41m"}  // SPACECRAFT
};


/*      DRAW FUNCTIONS     */

void renderer_set_pixel(int x, int y, char symbol, char fg_color[], char bg_color[]) {
    ScreenPixel temp_pixel;
	temp_pixel.symbol = symbol;
	strcpy(temp_pixel.fg_color, fg_color);
	strcpy(temp_pixel.bg_color, bg_color);
	if (x >= RENDERER_SCREEN_WIDTH | y >= RENDERER_SCREEN_HEIGHT | x < 0 | y < 0) return;
    renderer_screengrid[y][x] = temp_pixel;
}

// from_y has to be a lower value than to_y
void renderer_draw_line_vertical(int from_x, int from_y, int to_y) {
	for (int i = 0; i < to_y-from_y; i++) {
		ScreenPixel temp_pixel = {'|', "\x1b[37m", "\x1b[40m"};
    	renderer_screengrid[from_y+i][from_x] = temp_pixel;
	}
}

// from_x has to be a lower value than to_x
void renderer_draw_line_horizontal(int from_x, int from_y, int to_x) {
	for (int i = 0; i < to_x-from_x; i++) {
		ScreenPixel temp_pixel = {'-', "\x1b[37m", "\x1b[40m"};
    	renderer_screengrid[from_y][from_x+i] = temp_pixel;
	}
}

void renderer_draw_circle(int input_x, int input_y, int radius) {
	for (int y=-radius; y<=radius; y++) {
		for(int x=-radius; x<=radius; x++) {
			if(x*x+y*y <= radius*radius) {
				renderer_set_pixel(x + input_x, y + input_y, '.', "\x1b[32m", "\x1b[44m");
			}
		}
	}
}

void renderer_draw_text(char string[], int x, int y) {
	for (int i = 0; i < strlen(string); i++) {
		ScreenPixel temp_pixel = {string[i], "\x1b[37m", "\x1b[40m"};
    	renderer_screengrid[y][x+i] = temp_pixel;
	}
}

void renderer_draw_orbitview(int x, int y, int width, int height, int scale, char x_axis_symbol, char y_axis_symbol) {
	//int earth_radius = renderer_convert_to_screen_coord(6371000, scale, 0);
    //renderer_draw_circle(x+width/2, y+height/2, earth_radius);
    renderer_draw_line_vertical(x, y, y+height);
    renderer_set_pixel(x+1, y, y_axis_symbol, "\x1b[37m", "\x1b[40m");
    renderer_draw_line_horizontal(x+1, y+height-1, x+width);
	renderer_set_pixel(x+width-1, height-2, x_axis_symbol, "\x1b[37m", "\x1b[40m");
}

void renderer_render_all_views(void) {
	for (int i = 0; i < sizeof(renderer_views)/sizeof(renderer_views[0]); i++) {
		//int earth_radius = renderer_convert_to_screen_coord(6371000, renderer_views[i].scale, 0);
        //renderer_draw_circle(/2, y+height/2, earth_radius);
		renderer_draw_orbitview(
			RENDERER_ORBIT_VIEW_WIDTH*renderer_views[i].view_x, 
			RENDERER_ORBIT_VIEW_HEIGHT*renderer_views[i].view_y, 
			RENDERER_ORBIT_VIEW_WIDTH, 
			RENDERER_ORBIT_VIEW_HEIGHT, 
			renderer_views[i].scale,
			renderer_views[i].x_axis_symbol, 
			renderer_views[i].y_axis_symbol
		);
	}


	// XZ
	//renderer_draw_orbitview(RENDERER_ORBIT_VIEW_WIDTH, 0, RENDERER_ORBIT_VIEW_WIDTH, RENDERER_ORBIT_VIEW_HEIGHT, 'x', 'z');

	// XZ
    //renderer_draw_orbitview(2*RENDERER_ORBIT_VIEW_WIDTH, 0, RENDERER_ORBIT_VIEW_WIDTH, RENDERER_ORBIT_VIEW_HEIGHT, 'x', 'y');
}


/*     CORE RENDERER FUNCTIONS    */

// TODO: vad fan gör den här funktionen här egentligen?
void renderer_fullstrcpy_internal(char dest[], const char source[], int dest_arry_size) {
	for (int i = 0; i < dest_arry_size; i++) {
		dest[i] = source[i];
	}
}

/* Much faster and does not require iteration */
void renderer_terminalclear_internal(void) {
	printf("\033[H\033[J");
}

/* Just places cursor, use printf after this function */
void renderer_gotoxy_internal(int x, int y) {
	printf("\033[%d;%dH", y, x);
}

void renderer_screenclear_internal(void) {
	for (int y = 0; y < RENDERER_SCREEN_HEIGHT; y++) {
		for (int x = 0; x < RENDERER_SCREEN_WIDTH; x++) {
			renderer_screengrid[y][x].symbol = ' ';
			renderer_fullstrcpy_internal(renderer_screengrid[y][x].fg_color, COLORCODE_FG_WHITE, sizeof(renderer_screengrid[y][x].fg_color));
			renderer_fullstrcpy_internal(renderer_screengrid[y][x].bg_color, COLORCODE_BG_BLACK, sizeof(renderer_screengrid[y][x].fg_color));
		}
	}
}

int renderer_render_screen(void) {
	renderer_terminalclear_internal();
	
	for (int y = 0; y < RENDERER_SCREEN_HEIGHT; y++) {
		for (int x = 0; x < RENDERER_SCREEN_WIDTH; x++) {	
			printf("%s%s%c", renderer_screengrid[y][x].fg_color, renderer_screengrid[y][x].bg_color, renderer_screengrid[y][x].symbol);
		}
		printf("\n");
	}
	printf("%s", COLORCODE_DEFAULT);	

    return 0;
}

void renderer_initialize(void) {
	renderer_screenclear_internal();
	//renderer_render_screen();
    printf("%s", COLORCODE_DEFAULT);
}




/*     RENDERER CALCULATIONS     */

int renderer_convert_to_screen_coord(int coord, int scale, int offset) {
	return (int)((coord / (float)scale) * RENDERER_ORBIT_VIEW_WIDTH) + offset;
}
