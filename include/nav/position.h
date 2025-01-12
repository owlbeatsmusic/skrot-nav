#ifndef POSITION_H_
#define POSITION_H_

#include "engine/space.h"
#include "common/vector.h"


int nav_update_orbit_previous_path(void);
int position_evaluate_current_position(void); // begin the Batch Filter

int position_update_distance_from_earth(CommunicationDataPacket *comm_data_packet);

/*
int position_request_radial_velocity(float distance);
int position_request_distance_from_earth(Vector3 velocity);
*/

int position_check_for_collisions_internal(SpaceObject *robot);

Vector3 position_predict_future_position_internal(SpaceObject obj, float time);


#endif
