#include <stdio.h>
#include <stdint.h>
#include "utils.h"

int16_t MOD_utils_read16(FILE*fp){
    /*
    printf("MOD_utils_read16(fp: %p)\n", fp);
    */
    uint8_t high = fgetc(fp);
    uint8_t low = fgetc(fp);
    int16_t result = (high<<8) | low;
    /*
    printf("<--\n");
    */
    return  result;
}
