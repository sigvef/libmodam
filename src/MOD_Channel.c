#include <stdio.h>
#include <stdlib.h>
#include "MOD_Channel.h"

MOD_Channel* MOD_Channel_load(int8_t *data){
    MOD_Channel* channel = (MOD_Channel*) malloc(sizeof(MOD_Channel));

    int8_t a = *data++;
    int8_t b = *data++;
    int8_t c = *data++;
    int8_t d = *data++;

    /* hope this is correct! :D */
    channel->sample  = (a & 0xf0) | ((c&0x3c)>>2);
    channel->sample_period = ((a&0x0f)<<10) | (b<<2) | ((c&0xc0)>>6);
    channel->effect =  ((c&0x0f)<<8) | d;

    return channel;
}
