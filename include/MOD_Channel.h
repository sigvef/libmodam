#ifndef MOD_CHANNEL_H
#define MOD_CHANNEL_H

#include <stdint.h>

typedef struct {
    int8_t sample;
    int16_t sample_period;
    int16_t effect;
} MOD_Channel;

MOD_Channel* MOD_Channel_load(FILE*fp);

#endif
