#include <stdio.h>
#include <math.h>

#include "../global.h"

/*
https://sv.wikipedia.org/wiki/Radar
https://dev.ti.com/tirex/explore/node?node=A__AHcIcGIuxqplVSvU7AwGCA__radar_toolbox__1AslXXD__LATEST
https://www.innosent.de/en/radar/
*/



// RADAR

void devices_radar_poweron(RadarDevice *radar) {

    return;
}

void devices_radar_shutdown(RadarDevice *radar) {

    return;
}

int devices_radar_scan(RadarDevice *radar) {

    /*  SKROT - REPLACE: IMPLEMENTATION OF RADAR HERE */

    for (float azimuth = radar->from_azimuth_angle; azimuth < radar->to_azimuth_angle; azimuth += radar->azimuth_step_size) {
        for (float elevation = radar->from_elevation_angle; elevation < radar->to_elevation_angle; elevation += radar->elevation_step_size) {
            for (int i = 0; i < MAX_SPACEOBJECTS; i++) {
                double dist = space_distance(radar->d.offset, spaceobjects[i].position);

                // Calculate azimuth and elevation to the object
                /*
                double object_azimuth = atan2(spaceobjects[i].y - radar->x, spaceobjects[i].x - radar->x) * 180.0 / M_PI;
                double object_elevation = atan2(spaceobjects[i].z - radar->z, sqrt((spaceobjects[i].x - radar->x) * (spaceobjects[i].x - radar->x) + 
                                                                            (spaceobjects[i].y - radar->y) * (spaceobjects[i].y - radar->y))) * 180.0 / M_PI;
                */
                double object_azimuth = atanf(fabs(radar->d.offset.y - spaceobjects[i].position.y) / fabs(radar->d.offset.x - spaceobjects[i].position.x));
                double object_elevation = atanf(fabs(radar->d.offset.z - spaceobjects[i].position.z) / fabs(radar->d.offset.x - spaceobjects[i].position.x));

                // Normalize angles to 0-360 degrees for azimuth
                if (object_azimuth < 0) object_azimuth += 360.0;

                // Check if the object is within the current azimuth and elevation sweep and within range
                if (dist <= radar->max_range && 
                    fabs(object_azimuth - azimuth) < radar->azimuth_step_size &&
                    fabs(object_elevation - elevation) < radar->elevation_step_size) {
                    printf("Detected object at (%.2f, %.2f, %.2f), distance: %.2f\n", spaceobjects[i].position.x, spaceobjects[i].position.y, spaceobjects[i].position.z, dist);
                }
            }
        }
    }
    return 0;
}




// LIDAR

void devices_lidar_poweron(LidarDevice *lidar) {

    return;
}

void devices_lidar_shutdown(LidarDevice *lidar) {

    return;
}

int devices_lidar_scan(LidarDevice *lidar) {

    /*  SKROT - REPLACE: IMPLEMENTATION OF LIDAR HERE */

    return 0;
}




// CAMERA

void devices_camera_poweron(CameraDevice *camera) {

    return;
}

void devices_camera_shutdown(CameraDevice *camera) {

    return;
}

int devices_camera_scan(CameraDevice *camera) {

    /*  SKROT - REPLACE: IMPLEMENTATION OF LIDAR HERE */

    return 0;
}




// CLAW

void devices_claw_poweron(ClawDevice *claw) {

    return;
}

void devices_claw_shutdown(ClawDevice *claw) {

    return;
}

int devices_claw_grab(ClawDevice *claw) {
    
    /*  SKROT - REPLACE: IMPLEMENTATION OF LIDAR HERE */

    return 0;
}




// BATTERY

// checks information about battery (eg: temperature)
int devices_battery_status(BatteryDevice *battery_device) {

    return 0;
}




// SOLAR PANEL

// updates information about solar panel (eg: sunlight coverage)

void devices_solarpanel_poweron(SolarPanelDevice *solar_panel) {

    return;
}

void devices_solarpanel_shutdown(SolarPanelDevice *solar_panel) {

    return;
}

int devices_solarpanel_status(SolarPanelDevice *solar_panel) {

    return 0;
}

int energy_adjust_solar_panels(SolarPanelDevice *solar_panel, Vector3 current_position, Vector3 sunlight_direction) {

    return 0;
}




// STORAGE

int devices_storage_write(StorageDevice *storage) {
    
    /*  SKROT - REPLACE: IMPLEMENTATION OF STORAGE HERE */

    return 0;
} 

int devices_storage_read(StorageDevice *storage) {
    
    /*  SKROT - REPLACE: IMPLEMENTATION OF STORAGE HERE */

    return 0;
} 
