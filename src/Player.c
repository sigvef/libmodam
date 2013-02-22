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

    MOD_PatternDivision* pattern_division; 

    MOD_Player_Channel* c0 = MOD_Player_Channel_create();
    MOD_Player_Channel* c1 = MOD_Player_Channel_create();
    MOD_Player_Channel* c2 = MOD_Player_Channel_create();
    MOD_Player_Channel* c3 = MOD_Player_Channel_create();


    while(1){

        pattern_division = mod->patterns[mod->pattern_table[player->song_position]]->divisions[player->active_division];

        uint8_t out = 0;
        out += MOD_Player_Channel_step(c0, mod, pattern_division->channels[0])*0.23;
        out += MOD_Player_Channel_step(c1, mod, pattern_division->channels[1])*0.23;
        out += MOD_Player_Channel_step(c2, mod, pattern_division->channels[2])*0.23;
        out += MOD_Player_Channel_step(c3, mod, pattern_division->channels[3])*0.3;
        putchar(out);

        player->tick++;
        double song_thr = player->sample_rate/8;
        while(player->tick > song_thr){
            player->tick -= song_thr;
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
