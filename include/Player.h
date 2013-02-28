#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
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
    int vibrato_waveform;
    double vibrato_amplitude;
    double vibrato_period;
    long vibrato_tick;
    int volume_speed;
    int volume;
    MOD_Sample* sample;
    const int8_t* sample_data;
    double sample_period;
    double sample_period_modifier;
    int number;
    double slide_period;
    double slide_target;
    double slide_speed;
} MOD_Player_Channel;

typedef struct{
    MOD_Player_Channel* channels[4];
    double tick;
    int song_position;
    int next_song_position;
    int active_division;
    int next_division;
    int ticks_per_division;
    double sample_rate;
    double tickticker_threshold;
    double tickticker;
    MOD* mod;
} MOD_Player;

MOD_Player* MOD_Player_create();
int16_t MOD_Player_play(MOD_Player* player, MOD* mod);
void MOD_Player_tick(MOD_Player* player, MOD* mod);
void MOD_Player_set_mod(MOD_Player* player, MOD* mod);
void MOD_Player_division(MOD_Player* player, MOD* mod);

MOD_Player_Channel* MOD_Player_Channel_create();
void MOD_Player_Channel_free(MOD_Player_Channel* channel);
int16_t MOD_Player_Channel_step(MOD_Player_Channel* player_channel, MOD_Player* player, MOD* mod);

void MOD_Player_Channel_set_volume(MOD_Player_Channel* player_channel, int volume);
void MOD_Player_Channel_process_effect(MOD_Player_Channel* player_channel, MOD_Player* player, MOD* mod, int effect);
void MOD_Player_Channel_division(MOD_Player_Channel* player_channel, MOD_Player* player, MOD* mod);
void MOD_Player_Channel_tick(MOD_Player_Channel* player_channel, MOD_Player* player, MOD* mod);

#endif
