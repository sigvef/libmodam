#ifndef MOD_SAMPLE_H
#define MOD_SAMPLE_H

typedef struct {
    char[22] name;
    int16_t length; /* in 16bit words */ 
    int8_t finetune;
    int8_t volume;
    int16_t repeat_offset;
    int16_t repeat_length;
    int8_t* data;
} MOD_Sample;

#endif
