#include <stdio.h>
#include <stdlib.h>
#include "MOD_Sample.h"
#include "utils.h"

MOD_Sample* MOD_Sample_load(const int8_t **data){

    MOD_Sample* sample = (MOD_Sample*) malloc(sizeof(MOD_Sample));

    for(int i=0;i<22;i++){
        sample->name[i] = *(*data)++;
    }

    sample->length = MOD_utils_read16(data);
    sample->finetune = *(*data)++;
    sample->volume = *(*data)++;
    sample->repeat_offset = MOD_utils_read16(data);
    sample->repeat_length = MOD_utils_read16(data);

    return sample;
}

void MOD_Sample_loadData(MOD_Sample* sample, const int8_t **data){
    sample->data = (int8_t*) malloc(sizeof(int8_t)*sample->length*2);
    for(int i=0;i<sample->length*2;i++){
        sample->data[i] = *(*data)++;
    }
}
