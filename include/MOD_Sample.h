#ifndef MOD_SAMPLE_H
#define MOD_SAMPLE_H

#include <stdio.h>
#include <stdint.h>


typedef struct {
    char name[22];
    uint16_t length; /* in 16bit words */ 
    int8_t finetune;
    uint8_t volume;
    uint16_t repeat_offset;
    uint16_t repeat_length;
} MOD_Sample;


MOD_Sample* MOD_Sample_load(const int8_t **data);

uint16_t MOD_Sample_get_length(MOD_Sample* sample);
uint16_t MOD_Sample_get_repeat_length(MOD_Sample* sample);
uint16_t MOD_Sample_get_length(MOD_Sample* sample);

#endif
