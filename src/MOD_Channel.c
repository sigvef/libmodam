#include <stdio.h>
#include <stdlib.h>
#include "MOD_Channel.h"

MOD_Channel* MOD_Channel_load(const int8_t **data){
    MOD_Channel* channel = (MOD_Channel*) malloc(sizeof(MOD_Channel));

    uint8_t a = *(*data)++;
    uint8_t b = *(*data)++;
    uint8_t c = *(*data)++;
    uint8_t d = *(*data)++;

    channel->sample  = (a & 0xf0) | ((c&0xf0)>>4);
    channel->sample_period = ((a&0x0f)<<8) | b;
    channel->effect =  ((c&0x0f)<<8) | d;

    return channel;
}
