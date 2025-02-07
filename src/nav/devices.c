/*
    DEVICES.C

    This file handles device interaction.

    (description updated: 2025-01-10)
*/

#include <stdio.h>
#include <math.h>

#include "nav/devices.h"
#include "engine/downlink.h"
#include "engine/renderer.h"
#include "engine/space.h"
#include "common/vector.h"
#include "common/print.h"
#include "awlib_log/log.h"

/*
https://sv.wikipedia.org/wiki/Radar
https://dev.ti.com/tirex/explore/node?node=A__AHcIcGIuxqplVSvU7AwGCA__radar_toolbox__1AslXXD__LATEST
https://www.innosent.de/en/radar/
*/



// GENERAL

void devices_poweron(Device *device) {
    device->powered_on = TRUE;
    return;
}

void devices_shutdown(Device *device) {
    device->powered_on = FALSE;
    return;
}



// RADAR

int devices_radar_scan(RadarDevice *radar) {
    if (radar->d.powered_on == FALSE) {
        printf("%sradar is not powered on\n", PRINT_ERROR);
        return -1;
    }


    /*  SKROT - REPLACE: IMPLEMENTATION OF RADAR HERE vvv */

    for (int i = 0; i < MAX_SPACEOBJECTS; i++) {
        double dist = vector_distance(radar->d.offset, spaceobjects[i].position);
        if (dist > radar->max_range)
            continue; 

        double dx = spaceobjects[i].position.x - radar->d.offset.x;
        double dy = spaceobjects[i].position.y - radar->d.offset.y;
        double dz = spaceobjects[i].position.z - radar->d.offset.z;

        // Calculate azimuth and elevation
        double object_azimuth = atan2(dy, dx) * 180.0 / M_PI;
        if (object_azimuth < 0)
            object_azimuth += 360.0;

        double horizontal_distance = sqrt(dx * dx + dy * dy);
        double object_elevation = atan2(dz, horizontal_distance) * 180.0 / M_PI;

        // Check if object falls within the radar scanning limits.
        if (object_azimuth >= radar->from_azimuth_angle && object_azimuth <= radar->to_azimuth_angle &&
            object_elevation >= radar->from_elevation_angle && object_elevation <= radar->to_elevation_angle)
        {
            printf("Detected object at (%.2f, %.2f, %.2f), distance: %.2f\n", 
                   spaceobjects[i].position.x, spaceobjects[i].position.y, spaceobjects[i].position.z, dist);
        }
    }
    return 0;
}


void device_radar_status(RadarDevice *radar, HealthData *health_data) {

    return;
}



// LIDAR

int devices_lidar_scan(LidarDevice *lidar) {

    if (lidar->d.powered_on == FALSE) {
        printf("%slidar is not powered on\n", PRINT_ERROR);
        return -1;
    }


    /*  SKROT - REPLACE: IMPLEMENTATION OF LIDAR HERE vvv */
     for (int i = 0; i < MAX_SPACEOBJECTS; i++) {
        double dist = vector_distance(lidar->d.offset, spaceobjects[i].position);

        if (dist <= lidar->max_range) {
            printf("%sDetected object at (%.2f, %.2f, %.2f), distance: %.2f\n", PRINT_DEBUG, spaceobjects[i].position.x, spaceobjects[i].position.y, spaceobjects[i].position.z, dist);
        }
    }

    return 0;
}

void device_lidar_status(LidarDevice *lidar, HealthData *health_data) {

    return;
}




// CAMERA

int devices_camera_scan(CameraDevice *camera) {

    if (camera->d.powered_on == FALSE) {
        printf("%scamera is not powered on\n", PRINT_ERROR);
        return -1;
    }

    /*  SKROT - REPLACE: IMPLEMENTATION OF CAMERA HERE */

    return 0;
}

void device_camera_status(CameraDevice *camera, HealthData *health_data) {

    return;
}



// CLAW

int devices_claw_grab(ClawDevice *claw) {

    if (claw->d.powered_on == FALSE) {
        printf("%sclaw is not powered on\n", PRINT_ERROR);
        return -1;
    }
    
    /*  SKROT - REPLACE: IMPLEMENTATION OF CLAW HERE */

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

void devices_transmitter_status(TransmitterDevice *transmitter, HealthData *health_data) {

    return;
}

int devices_transmitter_send_communication_packet(CommunicationDataPacket *comm_data_packet) {

    /*  SKROT - INSERT: IMPLEMENTATION OF TRANSMITTER SEND HERE (return -1 if failed & run analysis) */
    
    // this must be replaced in actual space:
    downlink_receive_communication_data_packet(*comm_data_packet);

    //printf("%s communication packet successfully sent (from transmitter)\n", PRINT_DONE);
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

int devices_run_telemetry_analysis(void) { // create HealthData

    // check all devices, create healthdata reports and save and continue if error occoured or any critical levels.



    return 0;
}

int devices_anomaly_found_protocol(HealthData health_data) { // from CDS(this) or other FP(fault protection) algorithms or downlink
    
    // eg. termniate device processes

    return 0;
}

int devices_enter_safing(void) {

    // types:
    // - simple; baseline safing instructions read from ROM
    // - complex; in CDS RAM, can be updated

    return 0;
}

// TODO : implement CLT (https://science.nasa.gov/learn/basics-of-space-flight/chapter11-1/)


void devices_lowpower_protocol_internal(void) {
    
    return;
}

