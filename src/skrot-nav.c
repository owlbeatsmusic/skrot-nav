#include <stdio.h>
#include "global.h"

int nav_spaceobjects_index = 0;

int nav_create() {
    nav_spaceobjects_index = space_append_spaceobject(SPACECRAFT, (Vector3){0, 0, EARTH_RADIUS + 1200000}, (Vector3){8000, 0, 0}, 20);
    if (nav_spaceobjects_index == -1) return -1;
    return 0;
}