/*
    ID.C

    This file handles ID:s for packets, devices, etc.

    (description updated: 2025-02-07)
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// index: 0=downlink, 1=spacecraft
void id_generate(char *dest, int index) {
    sprintf(dest, "%d%08X%04X", index, (unsigned int)time(NULL), rand() * 0xFFFF);
}
