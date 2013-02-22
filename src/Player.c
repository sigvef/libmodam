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

    MOD_Sample* sample = mod->samples[4];

    double sample_rate = 44100;
    double target_sample_rate = 44100;

    double sample_tracker = 0;

    int debug = 0;

    int tickticker = 0;
    
    int sample_id = -1;
    int new_sample_id = 1;
    int sample_period = 0;
    int effect = 0;

    int channel_id = 1;

    int tickspeed = 100000;

    double sample_ticker = 0;

    player->tick = 0;

    MOD_Pattern* pattern = mod->patterns[mod->pattern_table[player->song_position]];


    while(1){


    }
}
