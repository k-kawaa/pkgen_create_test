#include <stdlib.h>
#include <string.h>
#include "memory.h"

char *Malloc(){
    char *ptr;
    ptr = malloc(14);
    ptr[14 - 1] = '\0';
    return ptr;
}