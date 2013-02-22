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

            out = player_channel->sample_tracker < mod->samples[channel->sample-1]->length ? 127+(uint8_t)mod->samples[channel->sample-1]->data[((int)player_channel->sample_tracker)%mod->samples[channel->sample-1]->length] : 0;
        }else{
            out = 0;
        }
        player_channel->tick++;
        return out;
}
