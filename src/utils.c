#include <stdio.h>
#include <stdint.h>
#include "utils.h"

int16_t MOD_utils_read16(int8_t **data){
    uint8_t high = *(*data)++;
    uint8_t low = *(*data)++;
    int16_t result = (high<<8) | low;
    return  result;
}
