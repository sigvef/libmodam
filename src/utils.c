#include <stdint.h>
#include "utils.h"

/* Helper method to read a two-byte word */
int16_t MOD_utils_read16(const int8_t **data){
    uint8_t high = *(*data)++;
    uint8_t low = *(*data)++;
    int16_t result = (high<<8) | low;
    return  result;
}
