#ifndef FLIGHT_PATH_H_
#define FLIGHT_PATH_H_

#include "nav/communication.h"
#include "engine/space.h"

extern int nav_evaluate_drift_from_course(void);
extern int calculate_course_delta_velocity(void);

extern void nav_propulsion_set_destination_internal(Vector3 target);


extern void nav_update_tracked_objects_internal(int spaceobjects_index);
extern SpaceObject nav_identify_object_internal(RadarObject radar_obj);


#endif
