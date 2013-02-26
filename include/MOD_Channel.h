#ifndef MOD_CHANNEL_H
#define MOD_CHANNEL_H

#include <stdint.h>

typedef struct {
    int8_t sample;
    double sample_period;
    int16_t effect;
} MOD_Channel;

MOD_Channel* MOD_Channel_load(const int8_t **data);

#endif
