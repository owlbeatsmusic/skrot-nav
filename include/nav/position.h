#ifndef POSITION_H_
#define POSITION_H_

#include "engine/space.h"
#include "common/vector.h"


int nav_update_orbit_previous_path(void);
int nav_evaluate_current_position(void); // begin the Batch Filter

/*
int nav_communication_get_radial_velocity(float distance);
int nav_position_get_distance_from_earth(Vector3 velocity);
*/

int nav_check_for_collisions_internal(SpaceObject *robot);

Vector3 nav_predict_future_position_internal(SpaceObject obj, float time);


#endif
