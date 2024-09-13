#ifndef GLOBAL_H_
#define GLOBAL_H_


/*     GLOBAL      */

typedef struct {
    float x;
    float y;
    float z;
} Vector3;





/*     RENDERER      */

extern const char RENDERER_WARNING_PRINT[];
extern const char RENDERER_ERROR_PRINT[];
extern const char RENDERER_DEBUG_PRINT[];
extern const char RENDERER_DONE_PRINT[];

extern const int RENDERER_SCREEN_WIDTH;
extern const int RENDERER_SCREEN_HEIGHT;

// renderer - draw functions
void renderer_set_pixel(int x, int y);
void renderer_set_pixel_earth(int x, int y);
void renderer_draw_circle(int input_x, int input_y, int radius);
void renderer_draw_line_vertical(int from_x, int from_y, int to_y);
void renderer_draw_line_horizontal(int from_x, int from_y, int to_x);
void renderer_draw_text(char string[], int x, int y);
void renderer_draw_orbitview(int x, int y, int width, int height, char x_axis_symbol, char y_axis_symbol);

// renderer - core functions
void renderer_initialize();
int  renderer_render_screen();

// renderer - calculation functions
int  renderer_convert_to_screen_coord(int coord, int offset);





/*      SPACE       */

typedef enum {
    DEBRIS,
    SPACECRAFT
} SpaceObjectType;

typedef struct {
    SpaceObjectType type;
    Vector3 position;
    Vector3 velocity;
    float mass; 
} SpaceObject;

int space_append_spaceobject(SpaceObjectType type, Vector3 position, Vector3 velocity, float mass);

int space_start();




/*      SKROT-NAV       */

int nav_create();


#endif