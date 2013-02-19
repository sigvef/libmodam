#include <stdio.h>
#include <stdlib.h>
#include "MOD_Sample.h"
#include "utils.h"

MOD_Sample* MOD_Sample_load(FILE*fp){

    MOD_Sample* sample = (MOD_Sample*) malloc(sizeof(MOD_Sample));

    for(int i=0;i<22;i++){
        sample->name[i] = fgetc(fp);
    }

    sample->length = MOD_utils_read16(fp);
    sample->finetune = fgetc(fp);
    sample->volume = fgetc(fp);
    sample->repeat_offset = MOD_utils_read16(fp);
    sample->repeat_length = MOD_utils_read16(fp);

    return sample;
}

void MOD_Sample_loadData(MOD_Sample* sample, FILE*fp){
    sample->data = (int8_t*) malloc(sizeof(int8_t)*sample->length);
    for(int i=0;i<sample->length;i++){
        sample->data[i] = fgetc(fp);
    }
}
