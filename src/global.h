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
void renderer_set_pixel(int x, int y);
void renderer_set_pixel_earth(int x, int y);

int space_start();


#endif