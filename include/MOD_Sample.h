#ifndef MOD_SAMPLE_H
#define MOD_SAMPLE_H

#include <stdio.h>
#include <stdint.h>

typedef struct {
    char name[22];
    int16_t length; /* in 16bit words */ 
    int8_t finetune;
    int8_t volume;
    int16_t repeat_offset;
    int16_t repeat_length;
    int8_t* data;
} MOD_Sample;


MOD_Sample* MOD_Sample_load(int8_t **data);
void MOD_Sample_loadData(MOD_Sample* s, int8_t **data);
void MOD_Sample_free(MOD_Sample* s);

#endif
