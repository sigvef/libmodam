#include <stdio.h>
#include <stdlib.h>
#include "MOD_Sample.h"
#include "utils.h"

MOD_Sample* MOD_Sample_load(const int8_t **data){

    MOD_Sample* sample = (MOD_Sample*) malloc(sizeof(MOD_Sample));

    sample->name = *data;
    (*data) += 22;

    sample->length = MOD_utils_read16(data);
    sample->finetune = *(*data)++;
    sample->volume = *(*data)++;
    sample->repeat_offset = MOD_utils_read16(data);
    sample->repeat_length = MOD_utils_read16(data);

    return sample;
}

void MOD_Sample_loadData(MOD_Sample* sample, const int8_t **data){
    sample->name = data;
    *data += sample->length*2;
}
