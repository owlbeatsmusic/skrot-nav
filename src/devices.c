
/*
https://sv.wikipedia.org/wiki/Radar
https://dev.ti.com/tirex/explore/node?node=A__AHcIcGIuxqplVSvU7AwGCA__radar_toolbox__1AslXXD__LATEST
https://www.innosent.de/en/radar/

*/

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

int devices_radar_scan(RadarDevice *radar) {
    for (float azimuth = radar->from_azimuth_angle; azimuth < radar->to_azimuth_angle; azimuth += radar->azimuth_step_size) {
        for (float elevation = radar->from_elevation_angle; elevation < radar->to_elevation_angle; elevation += radar->elevation_step_size) {
            
        }
    }

    return 0;
}
