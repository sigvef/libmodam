#ifndef MOD_CHANNEL_H
#define MOD_CHANNEL_H

#include <stdint.h>

typedef struct {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
} MOD_Channel;

int MOD_Channel_get_sample(MOD_Channel* channel);
double MOD_Channel_get_sample_period(MOD_Channel* channel);
int MOD_Channel_get_effect(MOD_Channel* channel);

#endif
