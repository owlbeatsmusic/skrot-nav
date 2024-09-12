#ifndef GLOBAL_H_
#define GLOBAL_H_

extern const char COLORCODE_DEFAULT[];   
extern const char COLORCODE_FG_BLACK[];   
extern const char COLORCODE_BG_BLACK[];  
extern const char COLORCODE_FG_RED[];     
extern const char COLORCODE_BG_RED[];     
extern const char COLORCODE_FG_GREEN[]; 
extern const char COLORCODE_BG_GREEN[];  
extern const char COLORCODE_FG_YELLOW[]; 
extern const char COLORCODE_BG_YELLOW[]; 
extern const char COLORCODE_FG_BLUE[]; 
extern const char COLORCODE_BG_BLUE[]; 
extern const char COLORCODE_FG_MAGENTA[]; 
extern const char COLORCODE_BG_MAGENTA[]; 
extern const char COLORCODE_FG_CYAN[];   
extern const char COLORCODE_BG_CYAN[];    
extern const char COLORCODE_FG_WHITE[];   
extern const char COLORCODE_BG_WHITE[];

extern const int GLOBAL_SCREEN_WIDTH;
extern const int GLOBAL_SCREEN_HEIGHT;

void renderer_initialize();
int renderer_render_screen();
int renderer_convert_to_screen_coord(int coord, int offset);
void renderer_set_pixel(int x, int y);
void renderer_set_pixel_earth(int x, int y);
void renderer_draw_circle(int input_x, int input_y, int radius);
void renderer_draw_line_vertical(int from_x, int from_y, int to_y);
void renderer_draw_line_horizontal(int from_x, int from_y, int to_x);
void renderer_draw_text(char string[], int x, int y);
void renderer_draw_orbitview(int x, int y, int width, int height, char x_axis_symbol, char y_axis_symbol);

int space_start();


#endif