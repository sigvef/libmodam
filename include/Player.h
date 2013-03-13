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
    int sample_tracker;
    int tick;
    int volume_speed;
    int volume;
    MOD_Sample* sample;
    int sample_number;
    const int8_t* sample_data;
    int sample_period;
    int sample_period_modifier;
    int number;
    int slide_period;
    int slide_target;
    int slide_speed;
    int* sample_volumes;
} MOD_Player_Channel;

typedef struct{
    MOD_Player_Channel* channels[4];
    int tick;
    int song_position;
    int next_song_position;
    int active_division;
    int next_division;
    int ticks_per_division;
    int sample_rate;
    int microseconds;
    int microseconds_per_tick;
    int bpm;
    int division_loop_start;
    int division_loop_end;
    int division_loop_count;
    MOD* mod;
} MOD_Player;

MOD_Player* MOD_Player_create(int sample_rate);
int16_t MOD_Player_play(MOD_Player* player);
void MOD_Player_reset(MOD_Player* player, int sample_rate);
void MOD_Player_step(MOD_Player* player, int microseconds);
void MOD_Player_tick(MOD_Player* player);
void MOD_Player_set_mod(MOD_Player* player, MOD* mod);
void MOD_Player_division(MOD_Player* player);

MOD_Player_Channel* MOD_Player_Channel_create();
void MOD_Player_Channel_free(MOD_Player_Channel* channel);
int32_t MOD_Player_Channel_step(MOD_Player_Channel* player_channel, MOD_Player* player, MOD* mod);
void MOD_Player_Channel_reset(MOD_Player_Channel* player_channel);

void MOD_Player_Channel_set_volume(MOD_Player_Channel* player_channel, int volume);
void MOD_Player_Channel_process_effect(MOD_Player_Channel* player_channel, MOD_Player* player, MOD* mod, int effect);
void MOD_Player_Channel_division(MOD_Player_Channel* player_channel, MOD_Player* player, MOD* mod);
void MOD_Player_Channel_tick(MOD_Player_Channel* player_channel, MOD_Player* player, MOD* mod);

#endif
