#ifndef FLIGHT_PATH_H_
#define FLIGHT_PATH_H_

#include "nav/communication.h"
#include "engine/space.h"

typedef struct {
    Vector3 destination;
    uint32_t estimated_time;
} FlightPathManeuver;

typedef struct {
    Vector3 destination;
    uint32_t estimated_time;
} FlightPath;

extern void flightpath_drift_status(HealthData *health_data);

extern int flightpath_create_course_maneuver(FlightPathManeuver *manouver);
extern void flightpath_perform_maneuver(FlightPathManeuver *manouver);

int flightpath_update_path(FlightPath *flight_path);
int flightpath_create_path(FlightPath *flight_path);

#endif
