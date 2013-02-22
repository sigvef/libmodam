#include <stdlib.h>
#include "MOD.h"
#include "MOD_Channel.h"
#include "Player_Channel.h"

MOD_Player_Channel* MOD_Player_Channel_create(){
    MOD_Player_Channel* channel = (MOD_Player_Channel*) malloc(sizeof(MOD_Player_Channel));
    channel->sample_tracker = 0;
    channel->tick = 0;
    channel->sample_rate = 44100;
    channel->old_sample = 0;
    channel->old_period = 0;
    return channel;
}

uint8_t MOD_Player_Channel_step(MOD_Player_Channel* player_channel, MOD* mod, MOD_Channel* channel){

        int e = (channel->effect&0xf00) >> 8;
        int x = (channel->effect&0x0f0) >> 4;
        int y =  channel->effect&0x00f;
        switch(e){
            case EFFECT_ARPEGGIO:
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

                //player->ticks_per_division = speed;  
                break;
            default:
                break;
        }

        uint8_t out;
        if(channel->sample == 0){
            channel->sample = player_channel->old_sample;
            channel->sample_period = player_channel->old_period;
        }
        if(channel->sample != 0){
            if(player_channel->old_sample != channel->sample){
                player_channel->sample_tracker = 0;
            }
            player_channel->old_sample = channel->sample;
            player_channel->old_period = channel->sample_period;

            double thr = channel->sample_period/3500000.*player_channel->sample_rate*2;

            while(player_channel->tick > thr){
                player_channel->tick -= thr;
                player_channel->sample_tracker++;
                if(mod->samples[channel->sample-1]->repeat_length > 1){
                    while(player_channel->sample_tracker >= mod->samples[channel->sample-1]->length){
                        player_channel->sample_tracker -= mod->samples[channel->sample-1]->repeat_length; 
                    }
                }
            }

            out = player_channel->sample_tracker < mod->samples[channel->sample-1]->length ? (127+(uint8_t)mod->samples[channel->sample-1]->data[((int)player_channel->sample_tracker)%mod->samples[channel->sample-1]->length]) : 127;
        }else{
            out = 127;
        }
        player_channel->tick++;
        return out;
}
