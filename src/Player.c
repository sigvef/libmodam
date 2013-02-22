#include <stdlib.h>
#include "Player.h"
#include "MOD.h"

MOD_Player* MOD_Player_create(){
    MOD_Player* player = (MOD_Player*) malloc(sizeof(MOD_Player));
    player->tick = 0;
    player->song_position = 0;
    player->active_division = 0;
    player->ticks_per_division = 6;
    return player;
}

void MOD_Player_play(MOD_Player* player, MOD*mod){

    MOD_Sample* sample;
    double sample_rate = 44100;
    double target_sample_rate = 44100/2;
    double sample_tracker = 0;
    int sample_id = 5;
    int new_sample_id = 1;
    int sample_period;
    double sample_ticker = 0;
    double song_ticker = 0;
    MOD_Pattern* pattern; 


    while(1){

        pattern = mod->patterns[mod->pattern_table[player->song_position]];
        sample_id = pattern->divisions[player->active_division]->channels[2]->sample;
        sample_period = pattern->divisions[player->active_division]->channels[2]->sample_period;
        sample = mod->samples[sample_id-1];

        putchar((127+(uint8_t)sample->data[((int)sample_ticker)%sample->length]));  

        player->tick++;


        double thr = 0.00001*sample_rate*sample_period/(double)sample->length;

        while(player->tick > thr){
            player->tick -= thr;
            sample_ticker++;
        }

        song_ticker++;
        double song_thr = sample_rate/8;
        while(song_ticker > song_thr){
            song_ticker -= song_thr;
            fprintf(stderr, "sample_period: %i\n", sample_period);
            player->active_division++;
            if(player->active_division > 63){
                player->active_division = 0;
                player->song_position++;
            }
        }

    }
}
