#ifndef DEVICES_H_
#define DEVICES_H_

#include "nav/devices_types.h"
#include "nav/communication.h"
#include "common/vector.h"

/*
    SKROT - ADD: OTHER DEVICES
*/

extern void devices_poweron(Device *device);
extern void devices_shutdown(Device *deivce);

extern int devices_radar_scan(RadarDevice *radar);
extern void devices_radar_status(RadarDevice *radar, HealthData *health_data);

extern int devices_lidar_scan(LidarDevice *lidar);
extern void devices_lidar_status(LidarDevice *lidar, HealthData *health_data);

extern int devices_camera_scan(CameraDevice *camera);
extern void devices_camera_status(CameraDevice *camera, HealthData *health_data);

extern int devices_claw_grab(ClawDevice *claw);
extern void devices_claw_status(ClawDevice *claw, HealthData *health_data);

extern void devices_battery_status(BatteryDevice *battery, HealthData *health_data);

extern void devices_solarpanel_status(SolarPanelDevice *solar_panel, HealthData *health_data);
extern int devices_adjust_solar_panels(SolarPanelDevice *solar_panel, Vector3 current_position, Vector3 sunlight_direction);

extern void devices_transmittor_status(TransmittorDevice *transmittor, HealthData *health_data);
extern int devices_transmittor_send_communication_packet(CommunicationDataPacket *comm_data_packet);

extern int devices_storage_write(StorageDevice *storage);
extern int devices_storage_read(StorageDevice *storage);

#endif
