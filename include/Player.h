#ifndef PLAYER_H
#define PLAYER_H

#include "MOD.h"

#define WAVEFORM_SINE 0
#define WAVEFORM_RAMPDOWN 1
#define WAVEFORM_SQUARE 2
#define WAVEFORM_RANDOM 3
#define WAVEFORM_NO_RETRIGGER 4

typedef struct {
    double sample_tracker;
    double tick;
    double sample_rate;
    int old_sample;
    double old_period;
    int vibrato_waveform;
    double vibrato_amplitude;
    double vibrato_period;
    long vibrato_tick;
    int volume_speed;
    int volume;
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
