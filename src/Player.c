#include <stdlib.h>
#include "Player.h"
#include "MOD.h"

MOD_Player* MOD_Player_create(){
    MOD_Player* player = (MOD_Player*) malloc(sizeof(MOD_Player));
    player->tick = 0;
    player->song_position = 0;
    player->next_song_position = -1;
    player->active_division = 0;
    player->ticks_per_division = 6;
    player->sample_rate = 44100;
    player->channels[0] = MOD_Player_Channel_create(0);
    player->channels[1] = MOD_Player_Channel_create(1);
    player->channels[2] = MOD_Player_Channel_create(2);
    player->channels[3] = MOD_Player_Channel_create(3);
    player->tickticker_threshold = 10*AMIGA_FREQUENCY/(double)player->sample_rate;
    player->tickticker = 0;
    player->mod = 0;
    return player;
}

void MOD_Player_set_mod(MOD_Player* player, MOD* mod){
    player->song_position = mod->n_song_positions-1;
    player->tick = player->ticks_per_division;
    player->active_division = 63;
    MOD_Player_tick(player, mod);
}


int16_t MOD_Player_play(MOD_Player* player, MOD*mod){

    MOD_PatternDivision* pattern_division; 


        pattern_division = &mod->patterns[mod->pattern_table[player->song_position]].divisions[player->active_division];

        double out = 0;

        out += MOD_Player_Channel_step(player->channels[0], player, mod)*0.005;
        out += MOD_Player_Channel_step(player->channels[1], player, mod)*0.005;
        out += MOD_Player_Channel_step(player->channels[2], player, mod)*0.005;
        out += MOD_Player_Channel_step(player->channels[3], player, mod)*0.005;

        player->tickticker++;
        while(player->tickticker > player->tickticker_threshold){
            player->tickticker -= player->tickticker_threshold;
            MOD_Player_tick(player, mod);
        }

        return out;
}


void MOD_Player_tick(MOD_Player* player, MOD* mod){

    player->tick++;

    while(player->tick > player->ticks_per_division){
        player->tick -= player->ticks_per_division;
        MOD_Player_division(player, mod);
    }

    MOD_Player_Channel_tick(player->channels[0], player, mod);
    MOD_Player_Channel_tick(player->channels[1], player, mod);
    MOD_Player_Channel_tick(player->channels[2], player, mod);
    MOD_Player_Channel_tick(player->channels[3], player, mod);
}


void MOD_Player_division(MOD_Player* player, MOD* mod){

        player->active_division++;
        if(player->active_division > 63){
            player->active_division = 0;
            player->song_position++;
            if(player->song_position >= mod->n_song_positions){
                player->song_position = 0; 
            }
        }

        if(player->next_song_position != -1){
            player->song_position = player->next_song_position;
            player->next_song_position = -1;
        }

        if(player->next_division != -1){
            player->active_division = player->next_division;
            player->next_division = -1;
        }
        MOD_Player_Channel_division(player->channels[0], player, mod);
        MOD_Player_Channel_division(player->channels[1], player, mod);
        MOD_Player_Channel_division(player->channels[2], player, mod);
        MOD_Player_Channel_division(player->channels[3], player, mod);
}
