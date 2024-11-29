#include <stdio.h>
#include <math.h>

#include "nav/devices.h"
#include "engine/renderer.h"
#include "engine/space.h"
#include "common/vector.h"
#include "common/print.h"

/*
https://sv.wikipedia.org/wiki/Radar
https://dev.ti.com/tirex/explore/node?node=A__AHcIcGIuxqplVSvU7AwGCA__radar_toolbox__1AslXXD__LATEST
https://www.innosent.de/en/radar/
*/


// GENERAL

void devices_poweron(Device *device) {

    return;
}

void devices_shutdown(Device *deivce) {

    return;
}



// RADAR

int devices_radar_scan(RadarDevice *radar) {

    /*  SKROT - REPLACE: IMPLEMENTATION OF RADAR HERE */

    for (float azimuth = radar->from_azimuth_angle; azimuth < radar->to_azimuth_angle; azimuth += radar->azimuth_step_size) {
        for (float elevation = radar->from_elevation_angle; elevation < radar->to_elevation_angle; elevation += radar->elevation_step_size) {
            for (int i = 0; i < MAX_SPACEOBJECTS; i++) {
                double dist = vector_distance(radar->d.offset, spaceobjects[i].position);

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

void device_radar_status(RadarDevice *radar, HealthData *health_data) {

    return;
}



// LIDAR

int devices_lidar_scan(LidarDevice *lidar) {

    /*  SKROT - REPLACE: IMPLEMENTATION OF LIDAR HERE */

    return 0;
}

void device_lidar_status(LidarDevice *lidar, HealthData *health_data) {

    return;
}




// CAMERA

int devices_camera_scan(CameraDevice *camera) {

    /*  SKROT - REPLACE: IMPLEMENTATION OF LIDAR HERE */

    return 0;
}

void device_camera_status(CameraDevice *camera, HealthData *health_data) {

    return;
}



// CLAW

int devices_claw_grab(ClawDevice *claw) {
    
    /*  SKROT - REPLACE: IMPLEMENTATION OF LIDAR HERE */

    return 0;
}

void device_claw_status(ClawDevice *claw, HealthData *health_data) {

    return;
}




// BATTERY

// checks information about battery (eg: temperature)
void devices_battery_status(BatteryDevice *battery_device, HealthData *health_data) {

    return;
}




// SOLAR PANEL

// updates information about solar panel (eg: sunlight coverage)

void devices_solarpanel_status(SolarPanelDevice *solar_panel, HealthData *health_data) {

    return;
}

int devices_adjust_solar_panels(SolarPanelDevice *solar_panel, Vector3 current_position, Vector3 sunlight_direction) {

    return 0;
}




// TRANSMITTOR

void devices_transmittor_status(TransmittorDevice *transmittor, HealthData *health_data) {

    return;
}

int devices_transmittor_send_communication_packet(CommunicationDataPacket comm_data_packet) {

    /*  SKROT - INSERT: IMPLEMENTATION OF TRANSMITTOR SEND HERE (return -1 if failed & run analysis) */

    printf("%s communication packet succesfully sent (from transmittor)\n", PRINT_DONE);
    return 1;
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



// connection to nav

int nav_run_telemetry_analysis(void) { // create HealthData

    // check all devices, create healthdata reports and save and continue if error occoured or any critical levels.



    return 0;
}

int nav_anomalie_found_protocol(HealthData health_data) { // from CDS(this) or other FP(fault protection) algorithms or downlink
    
    // eg. termniate device processes

    return 0;
}

int nav_enter_safing(void) {

    // types:
    // - simple; baseline safing instructions read from ROM
    // - complex; in CDS RAM, can be updated

    return 0;
}

// TODO : implement CLT (https://science.nasa.gov/learn/basics-of-space-flight/chapter11-1/)


void nav_energy_lowpower_protocol_internal(void) {
    
    return;
}

