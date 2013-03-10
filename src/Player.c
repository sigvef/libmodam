#include <stdlib.h>
#include "Player.h"
#include "MOD.h"

/* allocates, inits and returns a MOD_Player */
MOD_Player* MOD_Player_create(int sample_rate){

    /* malloc... */
    MOD_Player* player = (MOD_Player*) malloc(sizeof(MOD_Player));
    player->channels[0] = MOD_Player_Channel_create(0);
    player->channels[1] = MOD_Player_Channel_create(1);
    player->channels[2] = MOD_Player_Channel_create(2);
    player->channels[3] = MOD_Player_Channel_create(3);

    /* ...init... */
    player->channels[0] = MOD_Player_Channel_create(0);
    player->channels[1] = MOD_Player_Channel_create(1);
    player->channels[2] = MOD_Player_Channel_create(2);
    player->channels[3] = MOD_Player_Channel_create(3);

    /* ...reset... */
    MOD_Player_reset(player, sample_rate);

    /* ...and finally return the player! */
    return player;
}


/* resets a player to its default state */
void MOD_Player_reset(MOD_Player* player, int sample_rate){

    /* init struct fields */
    player->tick = 0;
    player->song_position = 0;
    player->next_song_position = 0;
    player->next_division = 0;
    player->active_division = 0;
    player->ticks_per_division = 6;
    player->sample_rate = sample_rate;
    player->bpm = 125;
    player->microseconds_per_tick = 2500000/player->bpm;
    player->microseconds = 0;
    player->mod = NULL;
    player->division_loop_start = 0;
    player->division_loop_end = 0;
    player->division_loop_count = -1;

    int i;
    for(i=0;i<4;i++){
        MOD_Player_Channel_reset(player->channels[i]);
    }
}


/* Binds a mod to a player, effectively resetting the player */
void MOD_Player_set_mod(MOD_Player* player, MOD* mod){
    MOD_Player_reset(player, player->sample_rate);
    if(mod != NULL){
        player->mod = mod;
        {int i;for(i=0;i<4;i++){
            player->channels[i]->sample = NULL;
            {int j;for(j=0;j<31;j++){
                player->channels[i]->sample_volumes[j] = mod->samples[j].volume;
            }}
        }}
        //MOD_Player_tick(player);
    }
}


/* The main play function. Calling this function returns a single int16_t audio
 * sample. The internal state is also advanced. */
int16_t MOD_Player_play(MOD_Player* player){

    int32_t out = 0;

    /* generate sound for each of the four channels */
    out += MOD_Player_Channel_step(player->channels[0], player, player->mod);
    out += MOD_Player_Channel_step(player->channels[1], player, player->mod);
    out += MOD_Player_Channel_step(player->channels[2], player, player->mod);
    out += MOD_Player_Channel_step(player->channels[3], player, player->mod);

    /* return the collected scaled down sample */
    return out>>6;
}

void MOD_Player_step(MOD_Player*player, int microseconds){

    /* advance the internal state */
    player->microseconds += microseconds;
    while(player->microseconds > player->microseconds_per_tick){
        player->microseconds -= player->microseconds_per_tick;
        MOD_Player_tick(player);
    }
}


/* advances internal state with one MOD tick */
void MOD_Player_tick(MOD_Player* player){

    player->tick++;

    /* if we have ticked enough ticks, advance a division */
    while(player->tick > player->ticks_per_division){
        player->tick -= player->ticks_per_division;
        MOD_Player_division(player);
    }

    /* propagate the tick to the channels */
    MOD_Player_Channel_tick(player->channels[0], player, player->mod);
    MOD_Player_Channel_tick(player->channels[1], player, player->mod);
    MOD_Player_Channel_tick(player->channels[2], player, player->mod);
    MOD_Player_Channel_tick(player->channels[3], player, player->mod);
}


/* advances internal state with one MOD division */
void MOD_Player_division(MOD_Player* player){

    if(player->division_loop_count == 0 && player->active_division == player->division_loop_end){
        player->division_loop_count = -1;
        player->division_loop_start = 0;
    }
    if(player->division_loop_count > 0 && player->active_division == player->division_loop_end){
        player->division_loop_count--;
        player->active_division = player->division_loop_start;
    }else{
        player->active_division++;
    }

    /* if we have advanced enough divisions, advance a song position */
    if(player->active_division > 63){
        player->active_division = 0;
        player->song_position++;
        if(player->song_position >= player->mod->n_song_positions){
            player->song_position = 0; 
        }
    }

    /* if something has ordered a song position jump, do that */
    if(player->next_song_position != -1){
        player->song_position = player->next_song_position;
        player->next_song_position = -1;
    }

    /* if something has ordered a division jump, do that */
    if(player->next_division != -1){
        player->active_division = player->next_division;
        player->next_division = -1;
    }

    /* propagate the division step to the channels */
    MOD_Player_Channel_division(player->channels[0], player, player->mod);
    MOD_Player_Channel_division(player->channels[1], player, player->mod);
    MOD_Player_Channel_division(player->channels[2], player, player->mod);
    MOD_Player_Channel_division(player->channels[3], player, player->mod);
}
