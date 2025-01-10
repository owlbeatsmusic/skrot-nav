#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// index: 0=downlink, 1=spacecraft
void id_generate(char *dest, int index) {
    sprintf(dest, "%d%08X%04X", index, (unsigned int)time(NULL), rand() * 0xFFFF);
}
