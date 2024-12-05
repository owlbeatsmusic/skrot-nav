#ifndef FLIGHT_PATH_H_
#define FLIGHT_PATH_H_

#include "nav/communication.h"
#include "engine/space.h"

typedef struct {
    Vector3 destination;
    uint32_t estimated_time;
} FlightPathManouver;

typedef struct {
    Vector3 destination;
    uint32_t estimated_time;
} FlightPath;

extern void nav_drift_status(HealthData *health_data);

extern int nav_create_course_manouver(FlightPathManouver *manouver);
extern void nav_perform_manouver(FlightPathManouver *manouver);

int nav_update_flight_path(FlightPath *flight_path);
int nav_create_flight_path(FlightPath *flight_path);

#endif
