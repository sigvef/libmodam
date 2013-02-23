#include <stdlib.h>
#include <math.h>
#include "MOD.h"
#include "MOD_Channel.h"
#include "Player.h"
#include "utils.h"

#define PI 3.142592

MOD_Player_Channel* MOD_Player_Channel_create(){
    MOD_Player_Channel* channel = (MOD_Player_Channel*) malloc(sizeof(MOD_Player_Channel));
    channel->sample_tracker = 0;
    channel->tick = 0;
    channel->sample_rate = 44100;
    channel->old_sample = 0;
    channel->old_period = 0;
    channel->vibrato_waveform = WAVEFORM_SINE;
    channel->vibrato_amplitude = 0;
    channel->vibrato_period = 0;
    channel->vibrato_tick = 0;
    channel->volume_speed = 0;
    channel->volume = 64;
    return channel;
}

double MOD_Player_Channel_step(MOD_Player_Channel* player_channel, MOD_Player* player, MOD* mod, MOD_Channel* channel){

    if(channel->sample == 0){
        channel->sample = player_channel->old_sample;
        channel->sample_period = player_channel->old_period;
    }


    double sample_period = channel->sample_period;

    int e = (channel->effect&0xf00) >> 8;
    int x = (channel->effect&0x0f0) >> 4;
    int y =  channel->effect&0x00f;

    switch(e){

        case EFFECT_ARPEGGIO:
            ;int step = (int)(3*player->tick/player->ticks_per_division);
            if(step == 1){ sample_period /= pow(2, x/12.);}
            if(step == 2){ sample_period /= pow(2, y/12.);}
            break;

        case EFFECT_SLIDE_UP:
            break;
        case EFFECT_SLIDE_DOWN:
            break;
        case EFFECT_SLIDE_TO_NOTE:
            break;
        case EFFECT_VIBRATO:
            player_channel->vibrato_waveform = WAVEFORM_SINE;
            player_channel->vibrato_amplitude = y/16.;
            player_channel->vibrato_period = (x*player->ticks_per_division)/64.;
            player_channel->vibrato_tick++;
            break;
        case EFFECT_CONTINUE_SLIDE_TO_NOTE_AND_VOLUME_SLIDE:
            //player_channel->volume_speed =  x == 0 ? -y : x;
            break;
        case EFFECT_CONTINUE_VIBRATO_TO_NOTE_AND_VOLUME_SLIDE:
            //player_channel->volume_speed =  x == 0 ? -y : x;
            player_channel->vibrato_tick++;
            break;
        case EFFECT_TREMOLO:
            break;
        case EFFECT_UNUSED:
            break;
        case EFFECT_SET_SAMPLE_OFFSET:
            break;
        case EFFECT_VOLUME_SLIDE:
            player_channel->volume_speed =  x == 0 ? -y : x;
            break;
        case EFFECT_POSITION_JUMP:
            break;
        case EFFECT_SET_VOLUME:
            //player_channel->volume_speed =  0;
            //player_channel->volume =  (x<<4) | y;
            break;
        case EFFECT_PATTERN_BREAK:
            break;
        case EFFECT_EXTRAS:
            break;

        case EFFECT_SET_SPEED:

            ;int speed = x*16+y;
            if(speed == 0){
                speed = 1;
            }

            if(speed > 32){
                speed = (24 * speed)/6;
            }

            player->ticks_per_division = speed;  
            break;
        default:
            break;
    }

    double modifier = pow(2, 2*player_channel->vibrato_amplitude*sin(
        player_channel->vibrato_period*player_channel->vibrato_tick*player->sample_rate/150000000.*PI
    )/12.);

    //fprintf(stderr, "vt: %d, ampl: %f, modifier: %f\n",player_channel->vibrato_tick, player_channel->vibrato_amplitude, modifier);

    if(isnan(modifier)){
        modifier = 1;
    }

    sample_period /= modifier;


    player_channel->volume += player_channel->volume_speed;
    player_channel->volume = MAX(player_channel->volume, 0);
    player_channel->volume = MIN(player_channel->volume, 64);

    double out;
    if(channel->sample != 0){
        MOD_Sample* sample = mod->samples[channel->sample-1];

        if(player_channel->old_sample != channel->sample){
            player_channel->sample_tracker = 0;
        }
        player_channel->old_sample = channel->sample;
        player_channel->old_period = channel->sample_period;

        double thr = sample_period/3500000.*player_channel->sample_rate;

        while(player_channel->tick > thr){
            player_channel->tick -= thr;
            player_channel->sample_tracker++;
            if(sample->repeat_length*2 > 1){
                while(player_channel->sample_tracker >= sample->length*2){
                    player_channel->sample_tracker -= sample->repeat_length*2; 
                }
            }
        }

        if(player_channel->sample_tracker < sample->length*2){
            int di = ((int)player_channel->sample_tracker)%(sample->length*2);
            int di_next = ((int)player_channel->sample_tracker+1)%(sample->length*2);
            int current_byte = sample->data[di];
            int next_byte = sample->data[(di_next)];
            double progress = player_channel->tick/thr;
            progress = 0;
            out = LARP(current_byte, next_byte, progress) * sample->volume*0.5 * player_channel->volume/64.;
        }else{
            out = 0;
        }
    }else{
        out = 0;
    }
    player_channel->tick++;
    return out;
}
