#ifndef DEVICES_TYPES_H_
#define DEVICES_TYPES_H_

#include <stdlib.h>

#include "common/vector.h"


typedef struct {
    u_int16_t id;
    Vector3 offset;
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
} TransmittorDevice;

typedef struct {
    Device d;  
    int size;
} StorageDevice;


#endif
