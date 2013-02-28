#include <stdio.h>
#include <stdlib.h>
#include "MOD_Sample.h"
#include "utils.h"

uint16_t MOD_Sample_get_length(MOD_Sample* sample){
    return FLIP_ENDIANNESS_INT16(sample->length);

}

uint16_t MOD_Sample_get_repeat_length(MOD_Sample* sample){
    return FLIP_ENDIANNESS_INT16(sample->repeat_length);
}

uint16_t MOD_Sample_get_repeat_offset(MOD_Sample* sample){
    return FLIP_ENDIANNESS_INT16(sample->length);
}

