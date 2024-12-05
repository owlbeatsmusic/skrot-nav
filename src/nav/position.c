
#include "engine/space.h"
#include "common/vector.h"


Vector3 last_mathematical_position;   
Vector3 last_observed_position; 


int nav_evaluate_current_position(void) { // begin the Batch Filter

    return 0;
}


int nav_communication_receive_velocity(float distance) {

    return 0;
}

int nav_communication_receive_distance_from_earth(Vector3 velocity) {

    return 0;
}



int nav_check_for_collisions_internal(SpaceObject *robot) {

    return 0;
}

/* Can also be self. */
Vector3 nav_predict_future_position_internal(SpaceObject obj, float delta_time) {
    Vector3 v3 = {0, 0, 0};
    return v3;
}
