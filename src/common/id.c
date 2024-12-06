#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void id_generate(char *dest) {
    sprintf(dest, "%08X%04X", (unsigned int)time(NULL), rand() * 0xFFFF);
}
