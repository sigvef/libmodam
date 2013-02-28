#include <stdio.h>
#include <stdlib.h>
#include "MOD_Channel.h"

int MOD_Channel_get_sample(MOD_Channel* channel){
    return (channel->a & 0xf0) | ((channel->c&0xf0)>>4);   
}

double MOD_Channel_get_sample_period(MOD_Channel* channel){
    return (double)(((channel->a&0x0f)<<8) | channel->b);
}

int MOD_Channel_get_effect(MOD_Channel* channel){
    return ((channel->c&0x0f)<<8) | channel->d;
}
