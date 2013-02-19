#include <stdio.h>
#include <stdlib.h>
#include "MOD_Channel.h"

MOD_Channel* MOD_Channel_load(FILE*fp){
    /*
    printf("MOD_Channel_load(fp: %p)\n", fp);
    */
    MOD_Channel* channel = (MOD_Channel*) malloc(sizeof(MOD_Channel));

    int8_t a = fgetc(fp);
    int8_t b = fgetc(fp);
    int8_t c = fgetc(fp);
    int8_t d = fgetc(fp);

    /* hope this is correct! :D */
    channel->sample  = (a & 0xf0) | ((c&0x3c)>>2);
    channel->sample_period = ((a&0x0f)<<10) | (b<<2) | ((c&0xc0)>>6);
    channel->effect =  ((c&0x0f)<<8) | d;

    /*
    printf("<--\n");
    */
    return channel;
}
