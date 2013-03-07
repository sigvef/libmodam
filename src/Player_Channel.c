#include <stdlib.h>
#include <math.h>
#include "MOD.h"
#include "MOD_Channel.h"
#include "Player.h"
#include "utils.h"

#define PI 3.142592

#define TICKSTEP 80

/* allocates, inits and returns a MOD_Player */
MOD_Player_Channel* MOD_Player_Channel_create(int channel_number){

    /* malloc... */
    MOD_Player_Channel* channel = (MOD_Player_Channel*) malloc(sizeof(MOD_Player_Channel));

    /* ...init struct fields... */
    channel->sample_tracker = 0;
    channel->tick = 0;
    channel->vibrato_waveform = WAVEFORM_SINE;
    channel->vibrato_amplitude = 0;
    channel->vibrato_period = 0;
    channel->vibrato_tick = 0;
    channel->volume = 64;
    channel->sample = NULL;
    channel->sample_data = NULL;
    channel->number = channel_number;
    channel->sample_period_modifier = 1;
    channel->slide_target = 0;
    channel->slide_period = 0;

    /* ...and finally return the player! */
    return channel;
}

/* The main channel play function. This gets called by the player. */
int16_t MOD_Player_Channel_step(MOD_Player_Channel* player_channel, MOD_Player* player, MOD* mod){

    /* get a reference to the current channel for convenience */
    MOD_Channel* channel = &mod->patterns[mod->pattern_table[player->song_position]].divisions[player->active_division].channels[player_channel->number];

    /* make a copy of the base sample period so we can modify it later, if needed */
    int sample_period = player_channel->sample_period;

    /* hack to fix a rounding bug from the double -> int conversion */
    if(player_channel->sample_period_modifier == 0){
        player_channel->sample_period_modifier = 1<<15;
    }

    /* modify the sample period (vibrato effects, slides etc) */
    sample_period = (sample_period * player_channel->sample_period_modifier) / (1<<15);


    int16_t out;

    /* if we have a sample bound, play it */
    if(player_channel->sample != 0){

        /* convenience references */
        MOD_Sample* sample = player_channel->sample;
        const int8_t* sample_data = player_channel->sample_data;


        /* advance the sample tracker when needed to get the correct sample period */
        int thr = sample_period;
        while(player_channel->tick > thr){

            player_channel->tick -= thr;
            player_channel->sample_tracker++;

            /* if this is a repeating sample, repeat when neccessary */
            if(MOD_Sample_get_repeat_length(sample) > 1){
                while(player_channel->sample_tracker >= MOD_Sample_get_length(sample)*2){
                    player_channel->sample_tracker -= MOD_Sample_get_repeat_length(sample)*2; 
                }
            }
        }

        /* generate the sample to output */
        if(player_channel->sample_tracker < MOD_Sample_get_length(sample)*2){
            int di = ((int)player_channel->sample_tracker)%(MOD_Sample_get_length(sample)*2);
            int current_byte = sample_data[di];
            out = current_byte * (((int)sample->volume * (int)player_channel->volume)>>5);
        }else{
            out = 0;
        }

    /* if there is no sample bound, output 0 */
    }else{
        out = 0;
    }

    /* advance internal tick state */
    player_channel->tick += TICKSTEP;

    /* finally return the sample */
    return out;
}


/* Sets the volume of a channel. Volume is an int between 0 and 64. */
void MOD_Player_Channel_set_volume(MOD_Player_Channel* player_channel, int volume){
    volume = MAX(volume, 0);
    volume = MIN(volume, 64);
    player_channel->volume = volume;
}

/* process the current effect for a channel */
void MOD_Player_Channel_process_effect(MOD_Player_Channel* player_channel, MOD_Player* player, MOD* mod, int effect){

    /* get the nybbles out of the tri-nybble */
    int e = (effect&0xf00) >> 8;
    int x = (effect&0x0f0) >> 4;
    int y =  effect&0x00f;

    /* init the modifier to 1<<15, aka no modification */
    player_channel->sample_period_modifier = 1<<15;

    switch(e){

        /* This is a cool effect. It auto-arpeggiates a note to make a chord
         * based on the values of x and y. */
        case EFFECT_ARPEGGIO:
            ;int step = (int)(3*player->tick/player->ticks_per_division);
            if(step == 1){ player_channel->sample_period_modifier /= pow(2, x/12.);}
            if(step == 2){ player_channel->sample_period_modifier /= pow(2, y/12.);}
            break;

        /* Slides a note upwards at a speed given by x and y */
        case EFFECT_SLIDE_UP:
            if(x*16+y) player_channel->slide_speed = x*16+y;
            player_channel->slide_period -= player_channel->slide_speed;
            player_channel->slide_period = MAX(player_channel->slide_period, 113);
            player_channel->sample_period_modifier = (1<<15)*player_channel->slide_period/player_channel->sample_period;
            break;

        /* Slides a note downwards at a speed given by x and y */
        case EFFECT_SLIDE_DOWN:
            if(x*16+y) player_channel->slide_speed = x*16+y;
            player_channel->slide_period += player_channel->slide_speed;
            player_channel->slide_period = MIN(player_channel->slide_period, 856);
            player_channel->sample_period_modifier = (1<<15)*player_channel->slide_period/player_channel->sample_period;
            break;

        /* Slides a note towards another note a speed given by x and y */
        case EFFECT_SLIDE_TO_NOTE:
            if(x*16+y) player_channel->slide_speed = x*16+y;
            if(player_channel->slide_period < player_channel->slide_target){
                player_channel->slide_period += player_channel->slide_speed;
                if(player_channel->slide_period > player_channel->slide_target){
                    player_channel->slide_period = player_channel->slide_target;
                }
            } else if(player_channel->slide_period > player_channel->slide_target){
                player_channel->slide_period -= player_channel->slide_speed;
                if(player_channel->slide_period < player_channel->slide_target){
                    player_channel->slide_period = player_channel->slide_target;
                }
            }
            player_channel->sample_period_modifier = (1<<15)*player_channel->slide_period/player_channel->sample_period;
            break;


        /* oscillates the sample period to create a vibrato effect */
        case EFFECT_VIBRATO:
            player_channel->vibrato_waveform = WAVEFORM_SINE;
            if(y) player_channel->vibrato_amplitude = y/16.;
            if(x) player_channel->vibrato_period = x/64.;
            /* currently we disable this , as it is really slow and uses sin */
            /*
            player_channel->sample_period_modifier /= pow(2, player_channel->vibrato_amplitude*sin(
                player_channel->vibrato_period*player_channel->vibrato_tick*PI*2)/12.);
            */
            break;

        /* does what it says on the tin */
        case EFFECT_CONTINUE_SLIDE_TO_NOTE_AND_VOLUME_SLIDE:
            if(x != 0 || y != 0){
                if(player_channel->slide_period < player_channel->slide_target){
                    player_channel->slide_period += x*16+y;
                    if(player_channel->slide_period > player_channel->slide_target){
                        player_channel->slide_period = player_channel->slide_target;
                    }
                } else if(player_channel->slide_period > player_channel->slide_target){
                    player_channel->slide_period -= x*16+y;
                    if(player_channel->slide_period < player_channel->slide_target){
                        player_channel->slide_period = player_channel->slide_target;
                    }
                }
            }
            player_channel->sample_period_modifier = (1<<15)*player_channel->slide_period/player_channel->sample_period;
            MOD_Player_Channel_set_volume(player_channel, player_channel->volume + x == 0 ? -y : x);
            break;


        /* does what it says on the tin */
        case EFFECT_CONTINUE_VIBRATO_TO_NOTE_AND_VOLUME_SLIDE:
            MOD_Player_Channel_set_volume(player_channel, player_channel->volume + (x == 0 ? -y : x));
            /*
            player_channel->sample_period_modifier /= pow(2, 2*player_channel->vibrato_amplitude*sin(
                player_channel->vibrato_period*player_channel->vibrato_tick*PI)/12.);
            */
            break;

        /* not implemented */
        case EFFECT_TREMOLO:
            break;

        /* implemented! :D but it does nothing */
        case EFFECT_UNUSED:
            break;

        /* not implemented */
        case EFFECT_SET_SAMPLE_OFFSET:
            break;

        /* slides the volume according to a speed given by x and y */
        case EFFECT_VOLUME_SLIDE:
            if(x || y) player_channel->volume_speed = x== 0 ? -y : x;
            MOD_Player_Channel_set_volume(player_channel, player_channel->volume + player_channel->volume_speed);
            break;

        /* jumps to a given song position after the current division */
        case EFFECT_POSITION_JUMP:
            player->next_song_position = x*16+y;
            break;

        /* sets the volume for this channel */
        case EFFECT_SET_VOLUME:
            MOD_Player_Channel_set_volume(player_channel, (x<<4) | y);
            break;

        /* jumps to a given pattern after the current division */
        case EFFECT_PATTERN_BREAK:
            ;int division = x*10+y; /* yes, really 10 */
            if(player->next_song_position == -1) player->next_song_position = (player->song_position + 1) % mod->n_song_positions;
            player->next_division = division;
            break;

        /* not implemented */
        case EFFECT_EXTRAS:
            break;

        /* Changes the speed of the player. This implementation is slightly buggy,
         * as EVERY TRACKER HAS ITS OWN DEFINITION OF THIS, GRR. */
        case EFFECT_SET_SPEED:

            ;int speed = x*16+y;
            if(speed == 0){
                speed = 1;
            }

            if(speed > 32){
                speed = speed*4./128.;
                speed = 4;
            }

            player->ticks_per_division = speed;  
            break;
        default:
            break;
    }

}

/* advances a tick */
void MOD_Player_Channel_tick(MOD_Player_Channel* player_channel, MOD_Player* player, MOD* mod){
    
    /* convenience pointer */
    MOD_Channel* channel = &mod->patterns[mod->pattern_table[player->song_position]].divisions[player->active_division].channels[player_channel->number];

    /* process the current effect */
    MOD_Player_Channel_process_effect(player_channel, player, mod, MOD_Channel_get_effect(channel));

    /* advance the vibrato tick, which curently does nothing */
    player_channel->vibrato_tick++;

}

/* advances a division */
void MOD_Player_Channel_division(MOD_Player_Channel* player_channel, MOD_Player* player, MOD* mod){

    /* convenience pointer */
    MOD_Channel* channel = &mod->patterns[mod->pattern_table[player->song_position]].divisions[player->active_division].channels[player_channel->number];


    /* only do stuff if we have a sample bound */
    if(MOD_Channel_get_sample(channel) != 0){

        /* get the effect nybble */
        int effect = (MOD_Channel_get_effect(channel)&0xf00) >> 8;

        /* do effect-specific updates of channel state */
        if(effect == EFFECT_SLIDE_UP || effect == EFFECT_SLIDE_DOWN){
            player_channel->slide_period = player_channel->sample_period;
        }
        if(effect == EFFECT_SLIDE_TO_NOTE || effect == EFFECT_CONTINUE_SLIDE_TO_NOTE_AND_VOLUME_SLIDE){
            player_channel->slide_period = player_channel->sample_period;
            player_channel->slide_target = MOD_Channel_get_sample_period(channel);
        }

        /* refresh sample period */
        if(MOD_Channel_get_sample_period(channel)){
            player_channel->sample_period = MOD_Channel_get_sample_period(channel);
        }

        /* update more state from the channel */
        player_channel->sample = &mod->samples[MOD_Channel_get_sample(channel)-1];
        player_channel->sample_data = mod->sample_datas[MOD_Channel_get_sample(channel)-1];
        player_channel->sample_tracker = 0;
        MOD_Player_Channel_set_volume(player_channel, 64);
    }
}
