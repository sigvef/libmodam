#ifndef MOD_PLAYER_CHANNEL_H
#define MOD_PLAYER_CHANNEL_H

#include "MOD_Channel.h"

typedef struct {
    double sample_tracker;
    double tick;
    double sample_rate;
    int old_sample;
    int old_period;
} MOD_Player_Channel;

MOD_Player_Channel* MOD_Player_Channel_create();
void MOD_Player_Channel_free(MOD_Player_Channel* channel);
uint8_t MOD_Player_Channel_step(MOD_Player_Channel* player_channel, MOD* mod, MOD_Channel* channel);

#endif
