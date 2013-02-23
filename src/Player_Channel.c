#include <stdlib.h>
#include <math.h>
#include "MOD.h"
#include "MOD_Channel.h"
#include "Player.h"
#include "utils.h"

MOD_Player_Channel* MOD_Player_Channel_create(){
    MOD_Player_Channel* channel = (MOD_Player_Channel*) malloc(sizeof(MOD_Player_Channel));
    channel->sample_tracker = 0;
    channel->tick = 0;
    channel->sample_rate = 44100;
    channel->old_sample = 0;
    channel->old_period = 0;
    return channel;
}

uint8_t MOD_Player_Channel_step(MOD_Player_Channel* player_channel, MOD_Player* player, MOD* mod, MOD_Channel* channel){

    if(channel->sample == 0){
        channel->sample = player_channel->old_sample;
        channel->sample_period = player_channel->old_period;
    }

    int sample_period = channel->sample_period;

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
            break;
        case EFFECT_CONTINUE_SLIDE_TO_NOTE_AND_VOLUME_SLIDE:
            break;
        case EFFECT_CONTINUE_VIBRATO_TO_NOTE_AND_VOLUME_SLIDE:
            break;
        case EFFECT_TREMOLO:
            break;
        case EFFECT_UNUSED:
            break;
        case EFFECT_SET_SAMPLE_OFFSET:
            break;
        case EFFECT_VOLUME_SLIDE:
            break;
        case EFFECT_POSITION_JUMP:
            break;
        case EFFECT_SET_VOLUME:
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

    uint8_t out;
    if(channel->sample != 0){
        if(player_channel->old_sample != channel->sample){
            player_channel->sample_tracker = 0;
        }
        player_channel->old_sample = channel->sample;
        player_channel->old_period = channel->sample_period;

        double thr = sample_period/3500000.*player_channel->sample_rate;

        while(player_channel->tick > thr){
            player_channel->tick -= thr;
            player_channel->sample_tracker++;
            if(mod->samples[channel->sample-1]->repeat_length*2 > 1){
                while(player_channel->sample_tracker >= mod->samples[channel->sample-1]->length*2){
                    player_channel->sample_tracker -= mod->samples[channel->sample-1]->repeat_length*2; 
                }
            }
        }

        //out = player_channel->sample_tracker < mod->samples[channel->sample-1]->length*2 ? (127+(uint8_t)mod->samples[channel->sample-1]->data[((int)player_channel->sample_tracker)%mod->samples[channel->sample-1]->length*2]) : 127;
        if(player_channel->sample_tracker < mod->samples[channel->sample-1]->length*2){
            int di = ((int)player_channel->sample_tracker)%mod->samples[channel->sample-1]->length*2;
            int di_next = ((int)player_channel->sample_tracker+1)%mod->samples[channel->sample-1]->length*2;
            int8_t current_byte = mod->samples[channel->sample-1]->data[di];
            int8_t next_byte = mod->samples[channel->sample-1]->data[(di_next)];
            double progress = player_channel->tick/thr;
            out = LARP(current_byte, next_byte, progress);
        }else{
            127;
        }
    }else{
        out = 127;
    }
    player_channel->tick++;
    return out;
}
