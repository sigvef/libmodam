#include <stdlib.h>
#include "Player.h"
#include "Player_Channel.h"
#include "MOD.h"

MOD_Player* MOD_Player_create(){
    MOD_Player* player = (MOD_Player*) malloc(sizeof(MOD_Player));
    player->tick = 0;
    player->song_position = 0;
    player->active_division = 0;
    player->ticks_per_division = 6;
    player->sample_rate = 44100;
    return player;
}

void MOD_Player_play(MOD_Player* player, MOD*mod){

    MOD_Sample* sample;
    double sample_tracker = 0;
    int sample_id = 5;
    int new_sample_id = 1;
    int sample_period;
    double sample_ticker = 0;
    double song_ticker = 0;
    MOD_Pattern* pattern; 

    MOD_Player_Channel* c0 = MOD_Player_Channel_create();
    MOD_Player_Channel* c1 = MOD_Player_Channel_create();
    MOD_Player_Channel* c2 = MOD_Player_Channel_create();
    MOD_Player_Channel* c3 = MOD_Player_Channel_create();


    while(1){

        pattern = mod->patterns[mod->pattern_table[player->song_position]];
        sample_id = pattern->divisions[player->active_division]->channels[1]->sample;
        sample_period = pattern->divisions[player->active_division]->channels[1]->sample_period;
        sample = mod->samples[sample_id-1];


        player->tick++;

        uint8_t out = 0;
        out += MOD_Player_Channel_step(c0, mod, pattern->divisions[player->active_division]->channels[0])*0.23;
        out += MOD_Player_Channel_step(c1, mod, pattern->divisions[player->active_division]->channels[1])*0.23;
        out += MOD_Player_Channel_step(c2, mod, pattern->divisions[player->active_division]->channels[2])*0.23;
        out += MOD_Player_Channel_step(c3, mod, pattern->divisions[player->active_division]->channels[3])*0.3;
        putchar(out);



        song_ticker++;
        double song_thr = player->sample_rate/8;
        while(song_ticker > song_thr){
            song_ticker -= song_thr;
            player->active_division++;
            if(player->active_division > 63){
                player->active_division = 0;
                player->song_position++;
                if(player->song_position >= mod->n_song_positions){
                    player->song_position = 0; 
                }
            }
        }

    }
}
