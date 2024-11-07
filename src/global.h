#ifndef GLOBAL_H_
#define GLOBAL_H_


/*     GLOBAL      */

typedef struct {
    float x;
    float y;
    float z;
} Vector3;

typedef enum {
    DEBRIS,
    SPACECRAFT
} SpaceObjectType;

typedef struct {
    SpaceObjectType type;
    Vector3 position;
    Vector3 velocity;
    float mass; 
    float radius;
} SpaceObject;

typedef struct {
    u_int8_t communication_status;  // 0=offline, 1=online, 2=degraded

    u_int16_t battery_level;    
    u_int8_t battery_status;        // 0 = normal, 1 = warning, 2 = critical)

    float temperature; 
    u_int8_t thermal_status;        // 0 = normal, 1 = warning, 2 = critical)

    float fuel_level;             
    u_int8_t fuel_status;           // 0 = normal, 1 = warning, 2 = critical)

    float pressure;      
    u_int8_t pressure_status;       // 0 = normal, 1 = warning, 2 = critical)

    u_int16_t radiation;        
    u_int8_t radiation_level;       // 0 = normal, 1 = warning, 2 = critical)

    u_int8_t error_code;            // if not 0, error has occoured in device / substystem
    u_int32_t uptime;               

} HealthData;



/*      DEVICES      */

typedef struct {
    u_int16_t id;
    HealthData health_data;

    Vector3 offset; // ????? offset från vad ?
    const float mass;    // can't be updated in space => const

} Device;

typedef enum {
    CW,   // continuous wave (unmodulated continuous-wave)
    FSK,  // frequency shift keying (alternate two frequencies)
    FMCW, // frequency-modulated continuous wave 
} RadarModulationType;

// objects detected by radar
typedef struct {
    float speed;
    float distance;
    float direction;
    float angle;
} RadarObject;

typedef struct {

    Device d;

    int min_range;
    int max_range;

    float azimuth_step_size;
    float elevation_step_size;

    float from_azimuth_angle;
    float to_azimuth_angle;

    float from_elevation_angle;
    float to_elevation_angle;

    float devices_radar_frequency_band; // GHz
    RadarModulationType radarModulationType;    

} RadarDevice;

typedef struct {
    Device d;
} LidarDevice;

typedef struct {
    Device d;  
} CameraDevice;

typedef struct {
    Device d;  
} ClawDevice;

typedef struct {
    Device d;  
    float soc; 
} BatteryDevice;

typedef struct {
    Device d;  
    int size;
} SolarPanelDevice;

typedef struct {
    Device d;  
    int size;
} StorageDevice;

/*
    SKROT - ADD: OTHER DEVICES
*/

extern void devices_radar_poweron(RadarDevice *radar);
extern void devices_radar_shutdown(RadarDevice *radar);
extern int devices_radar_scan(RadarDevice *radar);

extern void devices_lidar_poweron(LidarDevice *lidar);
extern void devices_lidar_shutdown(LidarDevice *lidar);
extern int devices_lidar_scan(LidarDevice *lidar);

extern void devices_camera_poweron(CameraDevice *camera);
extern void devices_camera_shutdown(CameraDevice *camera);
extern int devices_camera_scan(CameraDevice *camera);

extern void devices_claw_poweron(ClawDevice *claw);
extern void devices_claw_shutdown(ClawDevice *claw);
extern int devices_claw_grab(ClawDevice *claw);

extern int devices_battery_status(BatteryDevice *battery);

extern void devices_solarpanel_poweron(SolarPanelDevice *solar_panel);
extern void devices_solarpanel_shutdown(SolarPanelDevice *solar_panel);
extern int devices_solarpanel_status(SolarPanelDevice *solar_panel);
extern int energy_adjust_solar_panels(SolarPanelDevice *solar_panel, Vector3 current_position, Vector3 sunlight_direction);

extern int devices_storage_write(StorageDevice *storage);
extern int devices_storage_read(StorageDevice *storage);




/*      SKROT-NAV       */

int nav_spaceobjects_index;

int nav_update(void);

int nav_create(void);









//----------------------------------------//
//                                        //
//         v     SIMULATION       v       //
//                                        //
//----------------------------------------//



/*      SPACE       */

extern const float G;
extern const float M;
extern const float DELTA_T;
extern const float EARTH_RADIUS;

typedef struct {
	char symbol;
	char fg_color[8];
	char bg_color[8];
} ScreenPixel;

extern const int MAX_SPACEOBJECTS;
extern SpaceObject spaceobjects[];

float space_distance(Vector3 a, Vector3 b);

int space_append_spaceobject(SpaceObjectType type, Vector3 position, Vector3 velocity, float mass);

int space_start(void);






/*     RENDERER      */

typedef struct {
	int view_x;
	int view_y;
    int center_object_index;
	int scale;
	char x_axis_symbol;
	char y_axis_symbol;
} View;

extern View renderer_views[3];

extern const ScreenPixel renderer_spaceobject_type_color[];

extern const char RENDERER_WARNING_PRINT[];
extern const char RENDERER_ERROR_PRINT[];
extern const char RENDERER_DEBUG_PRINT[];
extern const char RENDERER_DONE_PRINT[];

extern const int RENDERER_SCREEN_WIDTH;
extern const int RENDERER_SCREEN_HEIGHT;

extern const int RENDERER_ORBIT_VIEW_WIDTH;
extern const int RENDERER_ORBIT_VIEW_HEIGHT;

// renderer - draw functions
void renderer_set_pixel(int x, int y, char symbol, char fg_color[], char bg_color[]);
void renderer_draw_circle(int input_x, int input_y, int radius);
void renderer_draw_line_vertical(int from_x, int from_y, int to_y);
void renderer_draw_line_horizontal(int from_x, int from_y, int to_x);
void renderer_draw_text(char string[], int x, int y);
void renderer_draw_orbitview(int x, int y, int width, int height, int scale, char x_axis_symbol, char y_axis_symbol);
void renderer_render_all_views(void);

// renderer - core functions
void renderer_initialize(void);
int  renderer_render_screen(void);

// renderer - calculation functions
int  renderer_convert_to_screen_coord(int coord, int scale, int offset);



#endif
