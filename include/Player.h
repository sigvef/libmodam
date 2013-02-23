#ifndef PLAYER_H
#define PLAYER_H

#include "MOD.h"

typedef struct {
    double sample_tracker;
    double tick;
    double sample_rate;
    int old_sample;
    int old_period;
} MOD_Player_Channel;

typedef struct{
    MOD_Player_Channel* channels[4];
    double tick;
    int song_position;
    int active_division;
    int ticks_per_division;
    double sample_rate;
} MOD_Player;

MOD_Player* MOD_Player_create();
void MOD_Player_play(MOD_Player* player, MOD* mod);

MOD_Player_Channel* MOD_Player_Channel_create();
void MOD_Player_Channel_free(MOD_Player_Channel* channel);
double MOD_Player_Channel_step(MOD_Player_Channel* player_channel, MOD_Player* player, MOD* mod, MOD_Channel* channel);

#endif
